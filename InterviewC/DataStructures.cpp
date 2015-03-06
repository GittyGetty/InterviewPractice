#include <memory>
#include <vector>

#include "DataStructures.h"

/********************************************************************/
template <typename T> 
class FifoQueue {
public:
	FifoQueue(size_t size) {
		size_ = size;
		start_ = 0;
		elements_ = 0;
		queue_ = new T[size];
	}
	~FifoQueue() {
		delete queue_;
	}
	void enqueue(T item) {
		assert(elements_ < size_);

		size_t idx = (start_ + elements_) % size_;
		queue_[idx] = item;
		++elements_;
	}
	T dequeue() {
		assert(elements_ > 0);

		auto item = queue_[start_];
		start_ = (start_ + 1) % size_;
		--elements_;

		return item;
	}

private:
	size_t size_, start_, elements_;
	T* queue_;
};
/********************************************************************/
template <typename T>
class Array2D {
private:
	std::unique_ptr<T> array_;
	size_t y_;
public:
	Array2D(size_t x, size_t y) {
		array_.reset(new T[x * y]);
		y_ = y;
	}
	T* operator[](size_t p) {
		return array_.get() + p * y_;
	}
};
/********************************************************************/
void reverse_array_stl(int* a, size_t n) {
    std::reverse(a, a + n);
}
void reverse_array(int* a, size_t n) {
    for (size_t i = 0; i < n / 2; ++i)
        std::swap(a[i], a[n - i - 1]);
}
void reverse_vector(std::vector<int> v) {
    std::reverse(v.begin(), v.end());
}
/********************************************************************/