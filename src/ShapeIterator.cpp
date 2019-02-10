#include <cassert>

#include "ShapeIterator.hpp"

namespace dvmpredictor {
	ShapeIterator::ShapeIterator()
	{
		_has_next = false;
		Shape shape;
		_init(shape);
	}

	ShapeIterator::ShapeIterator(Shape shape)
	{
		_has_next = true;
		assert(shape.size() > 0);
		for (auto axis: shape) {
			assert(axis > 0);
		}
		_init(shape);
	}

	bool ShapeIterator::hasNext() const
	{
		return _has_next;
	}

	Coord ShapeIterator::next()
	{
		assert(_has_next);

		Coord ret = _next;

		for (int64_t dim = _shape.size() - 1; dim >= 0; --dim) {
			_next[dim]++;
			if (_next[dim] < _shape[dim])
				break;
			_next[dim] %= _shape[dim];
		}

		_has_next = _next[0] < _shape[0];

		return ret;
	}

	void ShapeIterator::_init(Shape shape)
	{
		_shape = shape;
		_next.resize(_shape.size());
		std::fill(_next.begin(), _next.end(), 0);
	}

	bool ShapeIterator::_inited() const
	{
		return _shape.size() > 0;
	}
}
