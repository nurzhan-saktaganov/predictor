#include <cassert>

#include "DArray.hpp"

namespace dvmpredictor {
	DArray::DArray() {}

	DArray::DArray(uint32_t id, Shape shape, size_t elem_size)
		: _id(id), _shape(shape), _elem_size(elem_size)
	{
		assert(id != id_undef);
		assert(elem_size > 0);

		assert(shape.size() > 0);
		for (size_t i = 0; i < shape.size(); ++i) {
			assert(shape[i] > 0);
		}
	}

	uint32_t DArray::id() const { return _id; }

	size_t DArray::elem_size() const { return _elem_size;}

	Shape DArray::shape() const { return _shape; }

	bool DArray::defined() const { return _shape.size() > 0; }
}
