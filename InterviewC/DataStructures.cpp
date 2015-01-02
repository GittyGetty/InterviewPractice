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
