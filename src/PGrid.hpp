#pragma once

#include "Shape.hpp"
#include "Template.hpp"
#include "DArray.hpp"
#include "DRule.hpp"
#include "Distribution.hpp"
#include "Node.hpp"
#include "Dispositions.hpp"
#include "ARule.hpp"

namespace dvmpredictor {
	class PGrid {
	public:
		PGrid();
		PGrid(Shape shape);

		bool is_inited() const;
		uint32_t dimensions() const;

		Template declare_template(Shape shape);
		DArray declare_array(Shape shape, size_t elem_size);

		void distribute(Template t, DRule r);
		void distribute(DArray a, DRule r);

		void redistribute(Template t, DRule r);
		void redistribute(DArray a, DRule r);

		void align_on(DArray a, Template t, ARule r);
		void align_on(DArray a, DArray b, ARule r);

		void realign_on(DArray a, Template t, ARule r);
		void realign_on(DArray a, DArray b, ARule r);
	private:
		bool _is_declared(Template t) const;
		bool _is_declared(DArray a) const;

		bool _is_distributed(Template t) const;
		bool _is_distributed(DArray a) const;

		Dispositions _distribute(Shape shape, DRule r) const;

		Dispositions _align_on(Shape shape, Dispositions d, ARule r) const;

		uint64_t _nodes_count() const;

		uint32_t _next_template_id;
		uint32_t _next_darray_id;

		Shape _shape;
		Distribution _distribution;

		mutable uint64_t _nodes_count_cache;
	};
}
