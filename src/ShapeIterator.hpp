#pragma once

#include "Shape.hpp"
#include "Coord.hpp"

namespace dvmpredictor {
	class ShapeIterator {
	public:
		ShapeIterator();
		ShapeIterator(Shape shape);

		bool hasNext() const;
		Coord next();
	private:
		void _init(Shape shape);
		bool _inited() const;

		Shape _shape;
		Coord _next;
		bool _has_next;
	};
}
