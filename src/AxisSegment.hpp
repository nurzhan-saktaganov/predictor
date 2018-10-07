#pragma once

#include <cstdint>

class AxisSegment {
public:
    AxisSegment();
    AxisSegment(uint64_t from, uint64_t to);
    void init(uint64_t from, uint64_t to);
    uint64_t from() const;
    uint64_t to() const;
    uint64_t size() const;
    bool is_empty() const;
    AxisSegment intersection(const AxisSegment &with) const;

    // returns empty segment
    static AxisSegment empty();
private:
    uint64_t _from;
    uint64_t _to;
    bool _empty;
};
