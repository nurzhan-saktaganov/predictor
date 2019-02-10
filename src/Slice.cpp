#include "slice.hpp"

namespace dvmpredictor {
	const Slice Slice::undef = Slice();

	Slice::Slice(uint32_t dimension = 0)
		: _dimension(dimension), _size(0), _size_computed(true) {}

	Slice::Slice(const Segments &segments)
		: _segments(segments)
	{
		assert(segments.size() > 0);

		for (const auto &segment : segments) {
			assert(!segment.is_empty());
		}

		_dimension = static_cast<uint32_t>(segments.size());
	}

	Segments Slice::segments() const
	{
		return _segments;
	}

	uint32_t Slice::dimension() const
	{
		return _dimension;
	}

	uint64_t Slice::size() const
	{
		if (!_size_computed) {
			_size = 1;
			for (const auto &segment: _segments) {
				_size *= segment.size();
			}
			_size_computed = true;
		}

		return _size;
	}

	bool Slice::is_empty() const
	{
		return size() == 0;
	}

	Slice Slice::intersection(const Slice &with) const
	{
		assert(dimension() == with.dimension());

		if (is_empty() || with.is_empty()) {
			return Slice::empty(dimension());
		}

		Segments segments(dimension());

		for (uint32_t i = 0; i < segments.size(); ++i) {
			auto a = _segments[i];
			auto b = with._segments[i];

			segments[i] = a.intersection(b);

			if (segments[i].is_empty()) {
				return Slice::empty(dimension());
			}
		}

		return Slice(segments);
	}
}
