#include <cassert>

#include "Template.hpp"

namespace dvmpredictor {
	Template::Template(){}

	Template::Template(uint32_t id, Shape shape)
		: _id(id), _shape(shape)
	{
		assert(id != id_undef);

		assert(shape.size() > 0);
		for (size_t i = 0; i < shape.size(); ++i) {
			assert(shape[i] > 0);
		}
	}

	uint32_t Template::id() const { return _id; }

	Shape Template::shape() const { return _shape; }

	bool Template::defined() const { return _shape.size() > 0; }
}
