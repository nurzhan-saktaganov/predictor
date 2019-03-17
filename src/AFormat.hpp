#include <cstdint>

namespace dvmpredictor {
	class AFormat {
	// AFormat represents parameters of the next align formulae: a*I + b
	public:
		AFormat();
		AFormat(uint32_t dim, int a, int b);

		bool defined() const;

		// The corresponding dimension's number
		uint32_t dimension() const;
		int a() const;
		int b() const;

		static const uint32_t dim_undefined = (uint32_t)-1;
	private:
		uint32_t _dimension;
		int _a;
		int _b;
	};
}
