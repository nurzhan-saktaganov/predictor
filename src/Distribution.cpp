#include "Distribution.hpp"

namespace dvmpredictor {
	Distribution::Distribution() {}

	void Distribution::dispose(Template t, Dispositions d)
	{
		_dispose(_templates_disposition, t.id(), d);
	}

	void Distribution::dispose(DArray a, Dispositions d)
	{
		_dispose(_arrays_disposition, a.id(), d);
	}

	Nodes Distribution::contain(Template t, Slice s)
	{
		assert(_is_disposed(t));
		return _contain(_templates_disposition[t.id()], s);
	}

	Nodes Distribution::contain(DArray a, Slice s)
	{
		assert(_is_disposed(a));
		return _contain(_arrays_disposition[a.id()], s);
	}

	Slice Distribution::disposed_on(Template t, Node n)
	{
		assert(_is_disposed(t));
		return _disposed_on(_templates_disposition[t.id()], n);
	}

	Slice Distribution::disposed_on(DArray a, Node n)
	{
		assert(_is_disposed(a));
		return _disposed_on(_arrays_disposition[a.id()], n);
	}

	Dispositions Distribution::of(Template t)
	{
		assert(_is_disposed(t));
		return _templates_disposition[t.id()];
	}

	Dispositions Distribution::of(DArray a)
	{
		assert(_is_disposed(a));
		return _arrays_disposition[a.id()];
	}

	// Private methods begin here

	void Distribution::_dispose(std::vector<Dispositions> &where, uint32_t at, Dispositions d)
	{
		if (at > where.size() - 1) {
			where.resize(at + 1);
		}

		where[at] = d;
	}

	Nodes Distribution::_contain(Dispositions &d, Slice s)
	{
		Nodes ret;

		for (auto & disposition: d) {
			if (disposition.second.intersection(s).is_empty()) {
				continue;
			}

			ret.push_back(disposition.first);
		}

		return ret;
	}

	Slice Distribution::_disposed_on(Dispositions &d, Node n)
	{
		Slice ret;

		for (auto & disposition: d) {
			if (disposition.first.id() != n.id())
				continue;

			ret = disposition.second;
		}

		return ret;
	}

	bool Distribution::_is_disposed(Template t) const
	{
		return t.id() < _templates_disposition.size()
			&& _templates_disposition[t.id()].size() > 0;
	}

	bool Distribution::_is_disposed(DArray a) const
	{
		return a.id() < _arrays_disposition.size()
			&& _arrays_disposition[a.id()].size() > 0;
	}
}
