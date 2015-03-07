/**********************************************************************/
template <typename T>
T msb_mask(T value) {
    T msb = 1 << (sizeof(T) * CHAR_BIT - 1);
    while ((msb & value) == 0) msb >>= 1;
    return msb;
}
/**********************************************************************/
void is_bit_palindrome_test();
void swap_nibbles_test();
/**********************************************************************/