#include <cassert>
#include <algorithm>

#include "Segment.hpp"

namespace dvmpredictor {
	const Segment Segment::empty = Segment();

	Segment::Segment() : _from(0) , _to(0) , _empty(true) {}

	Segment::Segment(int64_t from, int64_t to)
		: _from(from) , _to(to) , _empty(false)
	{
		assert(_from <= to);
	}

	int64_t Segment::from() const { return _from; }

	int64_t Segment::to() const { return _to; }

	uint64_t Segment::size() const
	{
		return is_empty() ? 0 : to() - from() + 1;
	}

	bool Segment::is_empty() const { return _empty; }

	Segment Segment::intersection(const Segment &with) const
	{
		if (is_empty() || with.is_empty())
			return Segment::empty;

		int64_t from = std::max(this->from(), with.from());
		int64_t to = std::min(this->to(), with.to());

		return from <= to ? Segment(from, to) : Segment::empty;
	}
}