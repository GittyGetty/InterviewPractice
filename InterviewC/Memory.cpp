#include <algorithm>

void reverse_memory(char* mem, size_t len) {
	std::reverse(mem, mem + len);
}
