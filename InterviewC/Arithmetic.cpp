#include <algorithm>
#include <tuple>

/***********************************************************/

std::tuple<size_t, size_t>* find_sub_with_sum
(unsigned int a[], size_t l, unsigned int s) {
	size_t i = 0;
	unsigned int cs = 0;

	for (size_t j = 0; j < l; j++) {
		cs += a[j];
		while (cs > s) cs -= a[i++];
		if (cs == s)
			return new std::tuple<size_t, size_t>(i, j);
	}
	return nullptr;
}

void find_sub_with_sum_driver()
{
	unsigned int a[] = { 0, 10, 5, 15, 20 };
	auto t = find_sub_with_sum(a, sizeof(a) / sizeof(unsigned int), 20);
}

/***********************************************************/

int median(const int a[], size_t n) {
	return (a[n / 2] + a[(n - 1) / 2]) / 2;
}

int median(const int a1[], const int a2[], size_t n) {
	if (n <= 0) return -1;
	if (n == 1) return (a1[0] + a2[0]) / 2;
	if (n == 2) return (std::max(a1[0], a2[0])
		+ std::min(a1[1], a2[1])) / 2;

	int m1 = median(a1, n);
	int m2 = median(a2, n);

	if (m1 > m2) std::swap(a1, a2);
	return median(a1 + (n - 1) / 2, a2, (n + 2) / 2);
}

/***********************************************************/

int max_sum(int* a, int n) {
	int max = 0, sum = 0;

	for (int i = 0; i < n; i++) {
		sum += a[i];
		sum = sum > 0 ? sum : 0;
		max = sum > max ? sum : max;
	}

	return max;
}

/***********************************************************/

int max_product(int a[], size_t n) {
	int mini = a[0], maxi = a[0], max = a[0];
	for (size_t i = 1; i < n; i++) {
		int maxp = a[i] * maxi;
		int minp = a[i] * mini;
		maxi = std::max(a[i], std::max(maxp, minp));
		mini = std::min(a[i], std::min(maxp, minp));
		max = std::max(maxi, max);
	}
	return max;
}
