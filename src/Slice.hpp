#pragma once

#include "Segments.hpp"

namespace dvmpredictor {
	class Slice {
	public:
		Slice(uint32_t dimension = 0);
		Slice(const Segments &segments);

		Segments segments() const;
		uint32_t dimension() const;
		uint64_t size() const;
		bool is_empty() const;

		Slice intersection(const Slice &with) const;

		static Slice empty(uint32_t dimension);
		static const Slice undef;
	private:
		Segments _segments;
		uint32_t _dimension;

		mutable uint64_t _size;
		mutable bool _size_computed;
	};
}
