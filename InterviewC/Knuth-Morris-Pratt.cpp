#include <memory>
#include <string>
#include <algorithm>
#include <vector>

/****************************************************************/

void build_t(const char *w, size_t n) {
	int *t = new int[n] { -1, 0 };
	size_t p = 2, c = 0;

	while (p < n) {
		if (w[p - 1] == w[c]) {
			t[p++] = ++c;
			printf("%d", t[p - 1]);
		}
		else if (c > 0)
			c = t[c];
		else {
			t[p++] = 0;
			printf("%d", t[p - 1]);
		}
	}
	printf("\n");
}

/****************************************************************/

typedef std::unique_ptr<ptrdiff_t[]> offset_table;

offset_table get_backtrack_table(const std::wstring &w) {
	size_t ws = std::max((size_t)2, w.size());
	auto t = offset_table(new ptrdiff_t[ws] { -1, 0 });
	size_t c = 2, p = 0;

	while (c < w.size()) {
		if (w[c - 1] == w[p]) t[c++] = ++p;
		else if (p > 0) p = t[p];
		else t[c++] = 0;
	}

	return t;
}

size_t kmp2(const std::wstring s, const std::wstring w) {
	offset_table t = get_backtrack_table(w);
	size_t m = 0, i = 0;

	while (m + i < s.size()) {
		while (s[m + i] == w[i]) i++;
		if (i == w.size()) return m;
		m += i - t[i];
		i = std::max((ptrdiff_t)0, t[i]);
	}

	return s.size();
}

/****************************************************************/

std::auto_ptr<ptrdiff_t> calculate_backtrack(const wchar_t* w, size_t wl) {
	ptrdiff_t *t = new ptrdiff_t[std::max(wl, (size_t)2)] {-1, 0};
	auto tp = std::auto_ptr<ptrdiff_t>(t);
	size_t p = 0, c = 2;
	while (c < wl) {
		if (w[c - 1] == w[p]) t[c++] = ++p;
		else if (p > 0) p = t[p];
		else t[c++] = 0;
	}
	return tp;
}

size_t kmp(const wchar_t* s, size_t sl, const wchar_t* w, size_t wl) {
	std::auto_ptr<ptrdiff_t> tp = calculate_backtrack(w, wl);
	ptrdiff_t *t = tp.get();

	size_t m = 0, i = 0;
	while (m + i < sl) {
		if (s[m + i] == w[i]) {
			if (i == wl - 1) return m;
			++i;
		}
		else {
			m += i - t[i];
			i = std::max((ptrdiff_t)0, t[i]);
		}
	}
	return wl;
}

// s: xxxxabcabcabdyyyyyy 
// w: abcabd
/*
std::cout << kmp2(L"xxxxabcabcabdyyyyyy", L"abcabd") << std::endl;
std::cout << kmp2(L"日本日本日本語日本語日本人日本日本日本日本日本", L"日本語日本人") << std::endl;
*/

/****************************************************************/
typedef std::wstring::size_type ssize;
ssize kmp_compact(const std::wstring &text, const std::wstring &pattern) {
	std::vector<ssize> offset(pattern.size(), 0);
	ssize p, t;

	for (t = 1, p = 0; t < pattern.size(); t++) {
		offset[t] = p;
		p = pattern[t] == pattern[p] ? p + 1 : offset[p];
	}
	
	t = 0; p = 0;
	while (t < text.size() && p < pattern.size()) {
		while (text[t] == pattern[p]) {
			t++; p++; 
			if (p == pattern.size()) return t - p;
		}		
		if (p == offset[p]) t++;
		p = offset[p];
	}

	return text.size();
}

/*
int main() {
	auto r1 = kmp3(L"xxxxabcabcabdyyyyyy", L"abcabd");
	auto r2 = kmp3(L"xxxxabcabcabdyyyyyy", L"abcabde");
	auto r3 = kmp3(L"abc", L"abc");
	auto r4 = kmp3(L"", L"");
	auto r5 = kmp3(L"abc", L"");
	auto r6 = kmp3(L"", L"abc");
}
*/