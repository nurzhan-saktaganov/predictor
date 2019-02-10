#pragma once

#include <cstdlib>
#include <cstdint>

#include "Shape.hpp"

namespace dvmpredictor {
	class DArray {
	public:
		DArray();
		DArray(uint32_t id, Shape shape, size_t elem_size);

		uint32_t id() const;
		size_t elem_size() const;
		Shape shape() const;
		bool defined() const;

		static const uint32_t id_undef = UINT32_MAX;
	private:
		uint32_t _id;
		Shape _shape; 
		size_t _elem_size;
	};
}
