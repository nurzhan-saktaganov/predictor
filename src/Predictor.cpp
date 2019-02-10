#include <cassert>

#include "Predictor.hpp"

namespace dvmpredictor {
	Predictor::Predictor() {};

	void Predictor::init(Shape pgrid)
	{
		assert(! _pgrid.is_inited());
		_pgrid = PGrid(pgrid);
	};

	Template Predictor::declare_template(Shape shape)
	{
		return _pgrid.declare_template(shape);
	}

	DArray Predictor::declare_array(Shape shape, size_t elem_size)
	{
		return _pgrid.declare_array(shape, elem_size);
	}

	void Predictor::distribute(Template t, DRule r)
	{
		_pgrid.distribute(t, r);
	}

	void Predictor::distribute(DArray a, DRule r)
	{
		_pgrid.distribute(a, r);
	}

	void Predictor::redistribute(Template t, DRule r)
	{
		_pgrid.redistribute(t, r);
	}

	void Predictor::redistribute(DArray a, DRule r)
	{
		_pgrid.redistribute(a, r);
	}

	void Predictor::align_on(DArray a, Template t)
	{
		_pgrid.align_on(a, t);
	}

	void Predictor::align_on(DArray a, DArray b)
	{
		_pgrid.align_on(a, b);
	}

	void Predictor::realign_on(DArray a, Template t)
	{
		_pgrid.realign_on(a, t);
	}

	void Predictor::realign_on(DArray a, DArray b)
	{
		_pgrid.realign_on(a, b);
	}
}
