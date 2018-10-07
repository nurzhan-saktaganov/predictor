#include "ArraySliceInfo.hpp"

ArraySliceInfo::ArraySliceInfo() : _dimension(0), _size(0), _size_computed(true) {}

ArraySliceInfo::ArraySliceInfo(int dimension) : _dimension(dimension), _size(0), _size_computed(true) {}

ArraySliceInfo::ArraySliceInfo(const Segments segments) : _size_computed(false)
{
    init(segments);
}

void ArraySliceInfo::init(const Segments segments)
{
    _segments = segments;
    _dimension = segments.size();
}

Segments ArraySliceInfo::segments() const
{
    return _segments;
}

int ArraySliceInfo::dimension() const
{
    return _dimension;
}

uint64_t ArraySliceInfo::size() const
{
    if (!_size_computed) {
        _size = 1;
        for (const AxisSegment &segment : _segments) {
            _size *= segment.size();
        }
        _size_computed = true;
    }

    return _size;
}

bool ArraySliceInfo::is_empty() const
{
    return this->size() == 0;
}

ArraySliceInfo ArraySliceInfo::intersection(const ArraySliceInfo& with) const
{
    assert(this->dimension() > 0 && with.dimension() > 0);
    assert(this->dimension() == with.dimension());

    if (this->is_empty() || with.is_empty()){
        return ArraySliceInfo::empty(this->dimension());
    }

    Segments segments(this->dimension());

    for (int i = 0; i < segments.size(); ++i) {
        AxisSegment a = this->_segments[i];
        AxisSegment b = with._segments[i];

        segments[i] = a.intersection(b);

        if (segments[i].is_empty()) {
            return ArraySliceInfo::empty(this->dimension());
        }
    }

    return ArraySliceInfo(segments);
}

ArraySliceInfo ArraySliceInfo::empty(int dimension)
{
    return ArraySliceInfo(dimension);
}
