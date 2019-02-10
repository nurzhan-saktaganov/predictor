#pragma once

#include <cstdint>

namespace dvmpredictor {
	class Segment {
	public:
		Segment();
		Segment(int64_t from, int64_t to);

		int64_t from() const;
		int64_t to() const;

		uint64_t size() const;
		bool is_empty() const;

		Segment intersection(const Segment &with) const;

		static const Segment empty;
	private:
		int64_t _from;
		int64_t _to;
		bool _empty;
	};
}
