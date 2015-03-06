#include <iostream>
#include <string>

/***********************************************************************/
namespace {
	class A {};
	class B : public A {};
	template<class T, class B> struct Derived_from {
		static void constraints(T* p) { B* pb = p; }
		Derived_from() { void(*p)(T*) = constraints; }
	};
	template<class T> class Container : Derived_from < T, A > {
		// ...
	};
}
/***********************************************************************/
template <typename T> using IsArithmetic =
typename std::enable_if<std::is_arithmetic<T>::value, T>::type;

template<typename T, typename = IsArithmetic<T>>
T get_median(T a[], std::size_t n) {
	return (a[(n - 1) / 2] + a[(n + 1) / 2]) / 2;
}
template<typename T, typename = IsArithmetic<T>>
T get_median_slow(T a1[], T a2[], std::size_t n) {
	std::vector<T> m;
	m.insert(m.end(), a1, a1 + n);
	m.insert(m.end(), a2, a2 + n);
	std::sort(m.begin(), m.end());
	return get_median(&m[0], m.size());
}
template<typename T, typename = IsArithmetic<T>>
T get_median(T a1[], T a2[], std::size_t n) {
	if (n <= 2) return get_median_slow(a1, a2, n);

	auto thread = [n](T a[]) { return get_median(a, n); };
	T m1 = std::async(std::launch::async, thread, a1).get();
	T m2 = std::async(std::launch::async, thread, a2).get();

	if (m1 > m2) std::swap(a1, a2);

	return get_median(a1 + (n - 1) / 2, a2, (n + 2) / 2);
}
/***********************************************************************/
template <int N>
struct Factorial {
	static const int value = N * Factorial<N - 1>::value;
};
template <>
struct Factorial < 0 > {
	static const int value = 1;
};
/***********************************************************************/
template <typename T> T max(T t1, T t2) {
	return std::max(t1, t2);
}
template <typename T> T max(T* t1, T* t2) {
	return std::max(*t1, *t2);
}
/***********************************************************************/
template <bool> struct bar {};
template <> struct bar < true > { typedef void t; };

template <int T, typename = bar<T == 10>::t> struct foo { static const int result = 1; };
/***********************************************************************/
template<typename T, void(T::*)(std::string) = &T::quack> struct IsDuck {};
template<typename T, typename = IsDuck<T>> void quack_duck(T t) { t.quack("Quack!"); }
template<typename T> void f2(T t) { t.quack("f2"); }

template<> void f2<int>(int) { };

class Duck {
public:
	void quack(std::string s) {
		std::cout << "This duck says: " << s << std::endl;
	}
};

class Mime {
public:
	void quack(std::string s) {
		std::cout << "I'm not really a duck!" << std::endl;
	}
};
/***********************************************************************/