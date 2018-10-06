#include <cassert>

#include <iostream>

#include "AxisSegment.hpp"
#include "ArraySliceInfo.hpp"

int main(int argc, char *argv[])
{
    std::cout<<"Starting tests\n";

    ArraySliceInfo cube2(
        Segments{
            AxisSegment(0, 1),
            AxisSegment(0, 1),
            AxisSegment(0, 1)
        }
    );

    assert(cube2.size() == 8);
    assert(cube2.dimension() == 3);
    assert(cube2.is_empty() == false);

    ArraySliceInfo cube1(
        Segments{
            AxisSegment(0, 0),
            AxisSegment(0, 0),
            AxisSegment(0, 0)
        }
    );

    assert(cube1.size() == 1);
    assert(cube1.dimension() == 3);

    ArraySliceInfo cube2shift(
        Segments{
            AxisSegment(1, 2),
            AxisSegment(1, 2),
            AxisSegment(1, 2)
        }
    );

    auto intersection = cube2.intersection(cube2shift);

    assert(intersection.size() == 1);
    assert(intersection.dimension() == 3);
    assert(intersection.is_empty() == false);

    auto empty = intersection.intersection(cube1);

    assert(empty.size() == 0);
    assert(empty.dimension() == 3);
    assert(empty.is_empty() == true);

    std::cout<<"Tests successfully passed!"<<std::endl;

    return 0;
}
