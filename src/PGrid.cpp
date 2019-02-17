#include <cassert>
#include <vector>
#include <algorithm>

#include "PGrid.hpp"
#include "ShapeIterator.hpp"

namespace dvmpredictor {
	// vector represents segments of node.
	// index is node id, value is segments of node with this id.
	using NodeSegments = std::vector<Segments>;

	PGrid::PGrid()
		: _next_template_id(0)
		, _next_darray_id(0)
		, _nodes_count_cache(0)
	{}

	PGrid::PGrid(Shape shape)
		: _next_template_id(0)
		, _next_darray_id(0)
		, _shape(shape)
		, _nodes_count_cache(0)
	{
		assert(shape.size() > 0);
		for (auto axis: shape) {
			assert(axis > 0);
		}
	}

	bool PGrid::is_inited() const
	{
		return _shape.size() > 0;
	}

	uint32_t PGrid::dimensions() const
	{
		assert(is_inited());
		return static_cast<uint32_t>(_shape.size());
	}

	Template PGrid::declare_template(Shape shape)
	{
		assert(_next_template_id != Template::id_undef);
		return Template(_next_template_id++, shape);
	}

	DArray PGrid::declare_array(Shape shape, size_t elem_size)
	{
		assert(_next_darray_id != DArray::id_undef);
		return DArray(_next_darray_id++, shape, elem_size);
	}

	void PGrid::distribute(Template t, DRule drule)
	{
		assert(is_inited());
		assert(_is_declared(t));
		assert(!_is_distributed(t));

		auto dispositions = _distribute(t.shape(), drule);

		_distribution.dispose(t, dispositions);
	}

	void PGrid::distribute(DArray a, DRule drule)
	{
		assert(is_inited());
		assert(_is_declared(a));
		assert(!_is_distributed(a));

		auto dispositions = _distribute(a.shape(), drule);

		_distribution.dispose(a, dispositions);
	}

	void PGrid::align_on(DArray a, Template t, ARule r)
	{
		assert(is_inited());
		assert(_is_declared(a));
		assert(_is_declared(t));
		assert(_is_distributed(t));
		assert(!_is_distributed(a));

		auto base = _distribution.of(t);
		auto dispositions = _align_on(a.shape(), base, r);

		_distribution.dispose(a, dispositions);
	}

	void PGrid::align_on(DArray a, DArray b, ARule r)
	{
		assert(is_inited());
		assert(_is_declared(a));
		assert(_is_declared(b));
		assert(_is_distributed(b));
		assert(!_is_distributed(a));

		auto base = _distribution.of(b);
		auto dispositions = _align_on(a.shape(), base, r);

		_distribution.dispose(a, dispositions);
	}

	// Private methods begin here

	uint64_t PGrid::_nodes_count() const
	{
		if (_nodes_count_cache > 0)
			return _nodes_count_cache;

		assert(is_inited());

		_nodes_count_cache = 1;

		for (auto side: _shape) {
			_nodes_count_cache *= side;
		}

		return _nodes_count_cache;
	}

	// Distributes given shape with drule.
	// Takes every dimension of given shape and distributes it over
	// pgrid dimension using correspondingly rule.
	Dispositions PGrid::_distribute(Shape shape, DRule drule) const
	{
		assert(shape.size() == drule.size());

		NodeSegments node_segments(_nodes_count());

		uint32_t current_pgrid_dim = 0; // current free pgrid dim
		for (uint32_t dim = 0; dim < drule.size(); ++dim) {
			DFormat dformat = drule[dim];

			uint64_t shape_dim_size = shape[dim];

			if (!dformat.distributes()) {

				for (auto it = ShapeIterator(_shape); it.hasNext(); )
				{
					Coord coord = it.next();
					Node node(_shape, coord);

					Segment segment(0, shape_dim_size);
					node_segments[node.id()].push_back(segment);
				}
				continue;
			}

			assert(current_pgrid_dim < dimensions());

			// how much procs available in given dimension
			uint64_t proc_dim_size = _shape[current_pgrid_dim];

			auto axis_distribution = dformat.distribute(shape_dim_size, proc_dim_size);

			for (auto it = ShapeIterator(_shape); it.hasNext(); )
			{
				Coord coord = it.next();
				Node node(_shape, coord);

				uint64_t index = coord[current_pgrid_dim];	// this is a number from 0 to proc_dim_size - 1
				auto segment = axis_distribution[index];
				node_segments[node.id()].push_back(segment);
			}

			current_pgrid_dim++;
		}

		// now we have got a segments array for each node,
		// let's convert it into dispositions.

		Dispositions dispositions(_nodes_count());

		for (auto it = ShapeIterator(_shape); it.hasNext(); )
		{
			Coord coord = it.next();
			Node node(_shape, coord);

			auto slice = Slice(node_segments[node.id()]); // getting slice from segments

			dispositions[node.id()] = Disposition(node, slice);
		}

		return dispositions;
	}

	// align a shape with disposition d using rule r.
	Dispositions  PGrid::_align_on(Shape shape, Dispositions d, ARule r) const
	{
		Dispositions ret;

		// check shape and arule are conform
		assert(shape.size() == r.size());

		// check dispositions and arule are conform
		{
			auto slice = d[0].second;
			auto base_dimension = slice.dimension();

			std::vector<bool> reserved(base_dimension); 
			std::fill(reserved.begin(), reserved.end(), false);

			for (const auto &rule: r) {
				if (!rule.defined()) continue;

				uint32_t dim = rule.dimension();

				assert(dim <= base_dimension);

				assert(! reserved[dim]);

				reserved[dim] = true;
			}
		}



		for (auto &disposition: d) {
			for (auto &rule: r) {
				// TODO: WTF??
			}
		}

		return ret;
	}

	Segment _aligned_on_segment(Segment s, AFormat f) //const
	{
		/*
		let's assume we have segment [k1, k2] and an another segment [i1, i2]
		aligned with former one by rule: a*I + b, I - index variable.
		i1, i2 are unknown, we have to find their values.
		i1 => a*i1 + b => k'1, k1 <= k'1 <= k2. Similar for i2.

		k'1 is the least k: (k - b) % a == 0 and k1 <= k.
		Assume k'1 = k1 + d1, where d1 = (a - r1) % a, r1 = (k1 - b) % a.

		Similar for k'2 is the greatest k: (k - b) % a == 0 and k <= k2.
		Assume k'2 = k2 - d2. d2 = r2, r2 = (k2 - b) % a.
		*/
		int64_t from, to;
		int a = f.a(), b = f.b();

		assert(!s.is_empty());
		assert(f.defined());

		// calculate i1
		{
			int64_t k1 = s.from();
			int64_t r1 = (k1 - b) % a;
			int64_t d1 = (a - r1) % a;
			int64_t k = k1 + d1;

			int64_t i1 = (k - b) / a;

			from = i1;
		}

		// calculate i2
		{
			int64_t k2 = s.to();
			int64_t r2 = (k2 - b) % a;
			int64_t d2 = r2;
			int64_t k = k2 - d2;

			int64_t i2 = (k - b) / a;

			to = i2;
		}

		return Segment(from, to);
	}
}
