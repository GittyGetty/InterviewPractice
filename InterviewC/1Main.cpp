#include <vector>
#include <cstdint>
#include <set>
#include <memory>
#include <ctime>
#include <iostream>

typedef std::wstring::size_type ssize;
std::set<std::wstring> longest_common_substrings(std::wstring s1, std::wstring s2);

template <typename T>
class Array2D {
private:
	std::unique_ptr<T> managed_array_;
	T* array_;
	size_t y_;

public:
	Array2D(size_t x, size_t y) {
		managed_array_.reset(new T[x * y]);
		array_ = managed_array_.get();
		y_ = y;
	}
	T* operator[](size_t p) {
		return &array_[p * y_];
	}
};

int main() {
//	auto r = sqrt1<double>(100.0f, 0.0001);
//	uint64_t r = long_multiplication(13, 12);
//	auto r = longest_common_substrings(L"abbabababbbabbbabb", L"xxababxxababbbabbbabyy");

	const size_t x = 1000, y = 10000, iterations = 1000;
	
	auto a = Array2D<int>(x, y);

	//int** a = new int*[x];
	//for (int i = 0; i < y; ++i)
	//	a[i] = new int[y];

	auto start = clock();

	for (size_t i = 0; i < iterations; ++i) {
		for (size_t xi = 0; xi < x; ++xi) {
			for (size_t yi = 0; yi < x; ++yi) {
				a[xi][yi] = i;
			}
		}
	}

	auto seconds = (clock() - start) / (float)CLOCKS_PER_SEC;
	std::cout << seconds << std::endl;
}
