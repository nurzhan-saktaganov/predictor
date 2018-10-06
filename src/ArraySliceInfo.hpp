#pragma once

#include <cstdint>
#include <cstddef>

#include <vector>

#include "AxisSegment.hpp"

using Segments = std::vector<AxisSegment>;

class ArraySliceInfo {
    public:
        ArraySliceInfo();
        ArraySliceInfo(int dimension);
        ArraySliceInfo(const Segments segments);
        void init(const Segments segments);
        Segments segments() const;
        int dimension() const;
        uint64_t size() const;
        bool is_empty() const;
        ArraySliceInfo intersection(const ArraySliceInfo &with) const;

        // returns empty slice of given dimension
        static ArraySliceInfo empty(int dimension);
    private:
        Segments _segments;
        int _dimension;
        mutable uint64_t _size;
        mutable bool _size_computed;
};
