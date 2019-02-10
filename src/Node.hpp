#pragma once

#include "Coord.hpp"
#include "Shape.hpp"

namespace dvmpredictor {
	class Node {
	public:
		Node();
		Node(Shape pgrid_shape, Coord coord);

		uint64_t id() const;

		Coord coord() const;

		static const uint64_t id_undef = UINT64_MAX;
	private:
		void _init(Shape pgrid_shape, Coord coord);

		bool _defined() const;

		Coord _coord;
		Shape _pgrid_shape;

		mutable uint64_t _id_cache;
	};
}