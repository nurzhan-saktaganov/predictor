#pragma once

#include <utility>
#include "Node.hpp"
#include "Slice.hpp"

namespace dvmpredictor {
	using Disposition = std::pair<Node, Slice>;
}
