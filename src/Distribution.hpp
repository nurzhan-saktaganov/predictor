#pragma once

#include <vector>

#include "Template.hpp"
#include "DArray.hpp"
#include "Dispositions.hpp"
#include "Node.hpp"
#include "Slice.hpp"
#include "Disposition.hpp"
#include "Nodes.hpp"

namespace dvmpredictor {
	class Distribution {
	public:
		Distribution();

		// saves template distribution info
		void dispose(Template t, Dispositions d);

		// saves darray distribubtion info
		void dispose(DArray a, Dispositions d);

		//  returns nodes that contain at least one element from template slice
		Nodes contain(Template t, Slice s);

		// returns nodes that contain at least one element from array slice
		Nodes contain(DArray a, Slice s);

		// returns template slice that disposed on given node
		Slice disposed_on(Template t, Node n);

		// returns darray slice that disposed on given node
		Slice disposed_on(DArray a, Node n);

		Dispositions of(Template t);
		Dispositions of(DArray a);
	private:
		void _dispose(std::vector<Dispositions> &where, uint32_t at, Dispositions d);
		Nodes _contain(Dispositions &d, Slice s);
		Slice _disposed_on(Dispositions &d, Node n);

		bool _is_disposed(Template t) const;
		bool _is_disposed(DArray a) const;

		std::vector<Dispositions> _templates_disposition;
		std::vector<Dispositions> _arrays_disposition;
	};
}
