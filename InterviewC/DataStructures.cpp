#include <memory>

template <typename T> class PriorityQueue {
public:
	PriorityQueue(size_t size) {
		size_ = size;
		start_ = 0;
		elements_ = 0;
		queue_ = new T[size];
	}

	~PriorityQueue() {
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
