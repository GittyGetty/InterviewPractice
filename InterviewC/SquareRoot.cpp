#include <limits>
#include <type_traits>
#include <cstdint>

float sqrt2(const float x) {
	union {
		float x;
		int i;
	} u;
	u.x = x;
	u.i = 0x5f3759df - (u.i >> 1);  // gives initial guess y0
	return x*u.x*(1.5f - 0.5f*x*u.x*u.x); // Newton step, repeating increases accuracy 
}

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

template <typename T> struct IEEE {
	static const long long bias = std::numeric_limits<T>::max_exponent - 1;
	static const auto mantissa_bits = std::numeric_limits<T>::digits - 1;
	static const auto sqrt_mask = bias << (mantissa_bits - 1);
};

template<typename T> using is_floating_point = typename std::enable_if<std::is_floating_point<T>::value, T>::type;

template <typename T, typename = is_floating_point<T>> 
T sqrt1(const T x, const T precision) {
	union {
		uint64_t i;
		T t;
	} u;

	u.t = x;
	u.i = (u.i >> 1) + IEEE<T>::sqrt_mask;

	while ((u.t * u.t) - x > precision) 
		u.t = (u.t + x / u.t) / 2;

	return u.t;
}

//int main() {
//	auto r1 = sqrt1(100.0f, 0.0001f);
//	auto r2 = sqrt1(100.0, 0.0001);
//	//auto r3 = sqrt1<int>(100, 1);
//	//uint64_t r = long_multiplication(13, 12);
//}
