#include "DistributedArray.hpp"
#include "AlignGraph.hpp"

AlignGraph::AlignGraph(uint32_t size = 0) : _size(0)
{
    resize(size);
}

uint32_t AlignGraph::size() const
{
    return _size;
}

void AlignGraph::resize(uint32_t size)
{
    if (size == _size) return;

    _aligned_on.resize(size);
    _aligns_on.resize(size);

    // set new elements to undef if new size is greater
    for (uint32_t i = _size; i < size; ++i) {
            _aligns_on[i] = DistributedArray::id_undef;
    }
    
    _size = size;
}

Arrays AlignGraph::aligned_on(DistributedArray a) const
{
    assert(a.defined());
    assert(a.id() < _size);
    return _aligned_on[a.id()];
}

DistributedArray AlignGraph::aligns_on(DistributedArray a) const
{
    assert(a.defined());
    assert(a.id() < _size);
    return _aligns_on[a.id()];
}

void AlignGraph::set_aligment(DistributedArray a, DistributedArray on)
{
    assert(a.defined() && on.defined());
    assert(a.id() < _size && on.id() < _size);
    _aligns_on[a.id()] = on.id();
    
}
