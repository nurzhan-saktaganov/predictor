#include "DFormat.hpp"

namespace dvmpredictor {
	DFormat::DFormat() : _format(UNDEF){};

	bool DFormat::distributes() const
	{
		bool ret = true;

		switch (_format) {
		case NONE:
			ret = false;
		case BLOCK:
		case MULT_BLOCK:
		case WGT_BLOCK:
		case GEN_BLOCK:
			break;
		case UNDEF:
		default:
			abort();
		}

		return ret;
	}

	AxisDistribution DFormat::distribute(uint64_t elements, uint64_t procs) const
	{
		AxisDistribution ret;

		switch (_format) {
			case NONE:
				ret = _none(elements, procs);
				break;
			case BLOCK:
				ret = _block(elements, procs);
				break;
			case MULT_BLOCK:
				ret = _mult_block(elements, procs);
				break;
			case WGT_BLOCK:
				ret = _wgt_block(elements, procs);
				break;
			case GEN_BLOCK:
				ret = _gen_block(elements, procs);
				break;
			case UNDEF:
			default:
				abort();
		}

		return ret;
	}

	void DFormat::none()
	{
		_format = NONE;
	}

	void DFormat::block()
	{
		_format = BLOCK;
	}

	AxisDistribution DFormat::_none(uint64_t elements, uint64_t procs) const
	{
		AxisDistribution ret(procs);

		for (uint64_t i = 0; i < procs; ++i) {
			ret[i] = Segment(0, elements - 1);
		}

		return ret;
	}

	AxisDistribution DFormat::_block(uint64_t elements, uint64_t procs) const
	{
		AxisDistribution ret(procs);

		if (elements < procs) {
			for (uint64_t i = 0; i < elements; ++i) {
				ret[i] = Segment(i, i);
			}

			return ret;
		}

		uint64_t to = -1;

		for (uint64_t i = 0; i < procs; ++i) {
			uint64_t count = (i + 1) * elements / procs - i * elements / procs;

			uint64_t from = to + 1;
			to = from + count - 1;

			ret[i] = Segment(from, to);
		}

		return ret;
	}

	AxisDistribution DFormat::_mult_block(uint64_t elements, uint64_t procs) const
	{
		AxisDistribution ret;

		assert(0 && "not implemented");

		return ret;
	}

	AxisDistribution DFormat::_wgt_block(uint64_t elements, uint64_t procs) const
	{
		AxisDistribution ret;

		assert(0 && "not implemented");

		return ret;
	}

	AxisDistribution DFormat::_gen_block(uint64_t elements, uint64_t procs) const
	{
		AxisDistribution ret;

		assert(0 && "not implemented");

		return ret;
	}
}
