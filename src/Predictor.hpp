#pragma once

#include "Shape.hpp"
#include "Template.hpp"
#include "DArray.hpp"
#include "DRule.hpp"
#include "PGrid.hpp"

namespace dvmpredictor {
	class Predictor {
	public:
		Predictor();

		void init(Shape pgrid);

		Template declare_template(Shape shape);
		DArray declare_array(Shape shape, size_t elem_size);

		void distribute(Template t, DRule r);
		void distribute(DArray a, DRule r);

		void redistribute(Template t, DRule r);
		void redistribute(DArray a, DRule r);

		void align_on(DArray a, Template t);
		void align_on(DArray a, DArray b);

		void realign_on(DArray a, Template t);
		void realign_on(DArray a, DArray b);
	private:
		PGrid _pgrid;
	};
}
