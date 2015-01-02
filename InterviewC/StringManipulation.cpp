#include <string>
#include <iostream>
#include <cstdio>

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