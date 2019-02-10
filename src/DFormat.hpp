#include "AxisDistribution.hpp"

namespace dvmpredictor {

	// Distribution format
	class DFormat {
	public:
		enum Format {
			UNDEF,
			NONE,
			BLOCK,
			MULT_BLOCK,
			WGT_BLOCK,
			GEN_BLOCK,
		};

		DFormat();

		bool distributes() const;
		AxisDistribution distribute(uint64_t elements, uint64_t procs) const;

		void none();
		void block();

	private:
		AxisDistribution _none(uint64_t elements, uint64_t procs) const;
		AxisDistribution _block(uint64_t elements, uint64_t procs) const;
		AxisDistribution _mult_block(uint64_t elements, uint64_t procs) const;
		AxisDistribution _wgt_block(uint64_t elements, uint64_t procs) const;
		AxisDistribution _gen_block(uint64_t elements, uint64_t procs) const;

		Format _format;
	};
}
