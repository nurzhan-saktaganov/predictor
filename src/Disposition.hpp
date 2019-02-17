#pragma once

#include <utility>
#include "Node.hpp"
#include "Slice.hpp"

namespace dvmpredictor {
	// Denotes that the given node contains the given slice.
	using Disposition = std::pair<Node, Slice>;
}
