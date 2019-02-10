#pragma once

#include <cstdint>

#include "Shape.hpp"

namespace dvmpredictor {
	class Template {
	public:
		Template();
		Template(uint32_t id, Shape shape);

		uint32_t id() const;
		Shape shape() const;
		bool defined() const;

		static const uint32_t id_undef = UINT32_MAX;
	private:
		uint32_t _id;
		Shape _shape;
	};
}
