#include "Node.hpp"

namespace dvmpredictor {
	Node::Node()
	{
		Shape pgrid_shape;
		Coord coord;
		_init(pgrid_shape, coord);
	}

	Node::Node(Shape pgrid_shape, Coord coord)
	{
		assert(_pgrid_shape.size() == _coord.size());
		assert(_coord.size() > 0);

		for (uint32_t dim = 0; dim < _coord.size(); ++dim) {
			assert(0 <= _coord[dim]);
			assert(_coord[dim] < _pgrid_shape[dim]);
		}

		_init(pgrid_shape, coord);
	}

	uint64_t Node::id() const
	{
		assert(_defined());

		if (_id_cache != id_undef)
			return _id_cache;

		_id_cache = 0;

		uint64_t multiplier = 1;
		for (uint32_t dim = 0; dim < _coord.size(); ++ dim) {
			_id_cache += _coord[dim] * multiplier;
			multiplier *= _pgrid_shape[dim];
		}

		assert(_id_cache != id_undef);

		return _id_cache;
	}

	bool Node::_defined() const
	{
		return _coord.size() > 0;
	}

	void Node::_init(Shape pgrid_shape, Coord coord)
	{
		_coord = coord;
		_pgrid_shape = pgrid_shape;
		_id_cache = id_undef;
	}
}
