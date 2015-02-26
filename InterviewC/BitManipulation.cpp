#include <vector>
#include <limits>

/**********************************************************************/
using bit_vector = std::vector<unsigned>;
bit_vector int_to_bits(unsigned i) {
	std::vector<unsigned> vi;
	while (i != 0) {
		vi.push_back(i & 1);
		i >>= 1;
	}
	return vi;
}
unsigned bits_to_int(bit_vector bits) {
	unsigned i = 0;
	for (size_t b = 0; b < bits.size(); b++)
		i += bits[b] << b;
	return i;
}
/**********************************************************************/
