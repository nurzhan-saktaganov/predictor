#include <cassert>

#include <algorithm>

#include "AxisSegment.hpp"

AxisSegment::AxisSegment() : _empty(true) {}

AxisSegment::AxisSegment(uint64_t from, uint64_t to)
{
    init(from, to);
}

void AxisSegment::init(uint64_t from, uint64_t to)
{
    assert(from <= to);
    _from = from;
    _to = to;
    _empty = false;
}

uint64_t AxisSegment::from() const
{
    return _from;
}

uint64_t AxisSegment::to() const
{
    return _to;
}

uint64_t AxisSegment::size() const
{
    return is_empty() ? 0 : to() - from() + 1;
}

bool AxisSegment::is_empty() const
{
    return _empty;
}

AxisSegment AxisSegment::intersection(const AxisSegment &with) const
{
    uint64_t from = std::max(this->from(), with.from());
    uint64_t to = std::min(this->to(), with.to());

    return from <= to
        ? AxisSegment(from, to)
        : AxisSegment::empty();
}

AxisSegment AxisSegment::empty()
{
    return AxisSegment();
}
