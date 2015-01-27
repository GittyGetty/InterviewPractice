#include <cstdint>

bool can_win(int* a, size_t n, int cur, int sum) {
	if (cur >= sum) return false;

	for (size_t i = 0; i < n; i++) {
		if (!can_win(a, n, cur + a[i], sum)) {
			//printf("%d\n", a[i]);
			return true;
		}
	}
	return false;
}