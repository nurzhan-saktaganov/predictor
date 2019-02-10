#pragma once

#include <vector>
#include <cstdint>

#include "DistributedArray.hpp"

using Arrays = std::vector<DistributedArray>;

class AlignGraph {
public:
    AlignGraph(uint32_t size);

    uint32_t size() const; 
    void resize(uint32_t size);

    Arrays aligned_on(DistributedArray a) const;
    DistributedArray aligns_on(DistributedArray a) const;

    void set_aligment(DistributedArray a, DistributedArray on);
private:
    std::vector<Arrays> _aligned_on;
    std::vector<uint32_t> _aligns_on;
    uint32_t _size;
};
