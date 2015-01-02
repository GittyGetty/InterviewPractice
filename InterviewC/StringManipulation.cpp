#include <string>
#include <iostream>
#include <cstdio>

/************************************************************************/

// Print the reverse of a string using recursion.
void print_reverse(std::wstring s) {
	if (s.size() == 0) return;
	printf("%c", s[s.size() - 1]);
	s = s.substr(0, s.size() - 1);
	print_reverse(s);
}

void print_reverse_test() {
	print_reverse(L"ABCDEF");
}

/************************************************************************/

void string_matcher(const char *s, size_t ss, const char *p, size_t ps) {
	unsigned long long lp['z' - 'a' + 1] = { 0 };

	for (size_t i = 0; i < ps; i++) lp[p[i] - 'a'] |= 1ULL << i;

	unsigned long long col = s[0] == p[0];

	for (size_t i = 1; i < ss; i++) {
		if (col & 1ULL << (ps - 1))
			printf("Match @ %zu\n", i + 1 - ps);
		col = (col << 1 | 1) & lp[s[i] - 'a'];
	}

	if (col & 1ULL << (ps - 1))
		printf("Match @ %zu\n", ss - ps + 1);
}
