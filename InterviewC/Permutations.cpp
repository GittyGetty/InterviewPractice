#include <numeric>
#include <ctime>
#include <string>
#include <vector>

void permute(char* s, size_t l) {
	int* p = new int[l];
	std::iota(p, p + l, 0);
	for (size_t i = 0; i < l; printf("%s\n", s)) {
		std::swap(s[i], s[i % 2 * --p[i]]);
		for (i = 1; p[i] == 0; i++) p[i] = (int)i;
	}
}

void backtrack(char *str, int p) {
	size_t len = strlen(str);

	if (p == len) {
		//printf("%s\n", str);
		return;
	}

	for (size_t i = p; i < len; i++) {
		std::swap(str[p], str[i]);
		permute(str, p + 1);
		std::swap(str[p], str[i]);
	}
}

/*********************************************************/

void heap_permute(char* s, size_t n) {
	if (n == 1)	{
		printf("%s\n", s);
		return;
	}

	for (int i = 0; i < n; i++)	{
		heap_permute(s, n - 1);
		std::swap(s[n % 2 ? 0 : i], s[n - 1]);
	}
}

/*********************************************************/

void quick_perm(std::wstring &s) {
	std::vector<size_t> p(s.size());
	std::iota(p.begin(), p.end(), 0);
	for (int i = 0; i < p.size(); printf("%ls\n", s.c_str())) {
		std::swap(s[i], s[(i % 2) * --p[i]]);
		for (i = 1; i < p.size() && p[i] == 0; ++i) p[i] = i;
	}
}

/*********************************************************/

void permute_driver() {
	//char s[] = "abcdefghijkl";
	//char s[] = "abc";
	char s[] = "abcdefghijk";

	clock_t begin = clock();

	heap_permute(s, strlen(s));
	//permute(s, strlen(s));
	//permute(s, 0);

	clock_t end = clock();
	double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
	printf("%f\n", elapsed_secs);
}