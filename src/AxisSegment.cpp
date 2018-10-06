#include <cassert>

#include "AxisSegment.hpp"

AxisSegment::AxisSegment() : AxisSegment(0, 0) {}

AxisSegment::AxisSegment(uint64_t from, uint64_t to)
{
    init(from, to);
}

void AxisSegment::init(uint64_t from, uint64_t to)
{
    assert(from <= to);
    _from = from;
    _to = to;
}

uint64_t AxisSegment::from() const
{
    return _from;
}

uint64_t AxisSegment::to() const
{
    return _to;
}
