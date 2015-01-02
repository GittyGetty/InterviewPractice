#include <cstdio>
#include <memory>

void counting_sort(int* a, size_t n, int k) {
	int* count = new int[k];
	memset(count, 0, sizeof(int) * k);

	for (int i = 0; i < n; i++) count[a[i] - 1]++;

	int sum = 0;
	for (int i = 0; i < k; i++) {
		int tmp = count[i];
		count[i] = sum;
		sum += tmp;
	}

	int* result = new int[n];
	for (int i = 0; i < n; i++) {
		result[count[a[i] - 1]] = a[i];
		count[a[i]]++;
	}

	for (int i = 0; i < n; i++) {
		printf("%d\n", result[i]);
	}
}
