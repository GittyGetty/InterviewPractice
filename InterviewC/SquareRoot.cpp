#include <limits>

float sqrt2(const float x) {
	union {
		float x;
		int i;
	} u;
	u.x = x;
	u.i = 0x5f3759df - (u.i >> 1);  // gives initial guess y0
	return x*u.x*(1.5f - 0.5f*x*u.x*u.x); // Newton step, repeating increases accuracy 
}

template <typename T> struct IEEE {
	static const long long bias = std::numeric_limits<T>::max_exponent - 1;
	static const auto mantissa_bits = std::numeric_limits<T>::digits - 1;
	static const auto sqrt_mask = bias << (mantissa_bits - 1);
};

double my_sqrt(double d) {
	auto i = (unsigned long long*)&d;
	*i = (*i >> 1) + (1023ll << 51);
	return d;
}

float my_sqrt(float f) {
	auto i = (unsigned long*)&f;
	*i = (*i >> 1) + (127ll << 22);
	return f;
}

double sqrt1(const float x, const double precision) {
	union {
		unsigned long long i;
		double d;
		float f;
	} u;

	// u.i = (u.i >> 1) + (127 << 22)
	u.f = x;
	u.i = (u.i >> 1) + IEEE<float>::sqrt_mask;
	float sqrt_float = u.f;

	u.d = (double)x;
	u.i = (u.i >> 1) + IEEE<double>::sqrt_mask;
	double sqrt_double = u.d;

	while ((u.d * u.d) - x > precision) {
		u.d = (u.d + x / u.d) / 2;
	}

	return u.d;
}