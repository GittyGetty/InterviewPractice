#include <bitset>
#include <iostream>
#include <limits>
#include <vector>

#include "BitManipulation.h"

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
// http://www.geeksforgeeks.org/check-binary-representation-number-palindrome/
bool is_bit_palindrome(unsigned x) {
    size_t t = sizeof(decltype(x)) * CHAR_BIT;
    unsigned l = 1 << (t - 1), r = 1;

    for (size_t i = 0; i < t / 2; ++i) {
        if ((x & l) != (x & r)) return false;
        l = l >> 1;
        r = r << 1;        
    }
    return true;
}
void is_bit_palindrome_test() {
    bool b;
    b = is_bit_palindrome((1 << 15) + (1 << 16)); // true
    b = is_bit_palindrome((1 << 31) + 1); // true
    b = is_bit_palindrome(7); // false
}
/**********************************************************************/
// http://www.geeksforgeeks.org/how-to-turn-off-a-particular-bit-in-a-number/
unsigned zero_bit(unsigned n, unsigned k) {
    if (k > sizeof(n) * CHAR_BIT - 1) return n;
    return n & ~(1 << k);
}
/**********************************************************************/
// http://www.geeksforgeeks.org/swap-two-nibbles-byte/
unsigned swap_nibbles(unsigned char byte) {
    return (byte & 0xF0) >> 4 | (byte & 0x0F) << 4;
}
void swap_nibbles_test() {
    unsigned char x;
    x = swap_nibbles(100); // 70
}
/**********************************************************************/