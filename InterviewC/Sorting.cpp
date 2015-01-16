#include <cstdio>
#include <memory>

void counting_sort(int* a, size_t n, size_t k) {
	size_t* count = new size_t[k];
	memset(count, 0, sizeof(size_t) * k);

	for (size_t i = 0; i < n; i++) count[a[i] - 1]++;

	int sum = 0;
	for (size_t i = 0; i < k; i++) {
		int tmp = count[i];
		count[i] = sum;
		sum += tmp;
	}

	int* result = new int[n];
	for (size_t i = 0; i < n; i++) {
		result[count[a[i] - 1]] = a[i];
		count[a[i]]++;
	}

	for (size_t i = 0; i < n; i++) {
		printf("%d\n", result[i]);
	}
}
