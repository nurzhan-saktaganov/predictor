#include <cassert>

#include "AFormat.hpp"

namespace dvmpredictor {
	AFormat::AFormat() : _dimension(dim_undefined) {}

	AFormat::AFormat(uint32_t dim, int a, int b)
		: _dimension(dim), _a(a), _b(b)
	{
		assert(_dimension != dim_undefined);
	}

	bool AFormat::defined() const
	{
		return _dimension != dim_undefined;
	}

	uint32_t AFormat::dimension() const
	{
		return _dimension;
	}

	int AFormat::a() const
	{
		return _a;
	}

	int AFormat::b() const
	{
		return _b;
	}
}
