#include <cstdio>
#include <vector>

void print_primes(const int n) {
	std::vector<bool> is_prime(n + 1, true);
	for (int i = 2; i <= n; ++i) {
		if (!is_prime[i]) continue;
		printf("%d is a prime number.\n", i);
		for (int m = i * i; m <= n; m += i) is_prime[m] = false;
	}
}
