#include <numeric>
#include <algorithm>
#include <tuple>
#include <vector>
#include <bitset>
#include <cstdint>

#include "BitManipulation.h"

/***********************************************************/
typedef std::tuple<size_t, size_t> range;
range find_sub_with_sum(const std::vector<unsigned> &a, unsigned s) {
    unsigned cs = 0;
    for (size_t start = 0, end = 0; end < a.size(); ++end) {
        cs += a[end];
        while (cs > s) cs -= a[start++];
        if (cs == s) return range(start, end);
    }
    return range(a.size(), a.size());
}
/*
auto t = find_sub_with_sum({ 0, 10, 5, 15, 20 }, 20);
*/
/***********************************************************/
int median(const int a[], size_t n) {
    return (a[n / 2] + a[(n - 1) / 2]) / 2;
}
int median(const int a1[], const int a2[], size_t n) {
    if (n <= 0) return -1;
    if (n == 1) return (a1[0] + a2[0]) / 2;
    if (n == 2) return (std::max(a1[0], a2[0]) + std::min(a1[1], a2[1])) / 2;

    int m1 = median(a1, n);
    int m2 = median(a2, n);

    if (m1 > m2) std::swap(a1, a2);
    return median(a1 + (n - 1) / 2, a2, (n + 2) / 2);
}
/***********************************************************/
int max_sum(const std::vector<int> &a) {
    if (a.empty()) return 0;
    int maxi = a[0], max = a[0];
    for (size_t i = 1; i < a.size(); ++i) {
        maxi = std::max(maxi + a[i], 0);
        max = std::max(max, maxi);
    }
    return max;
}
/***********************************************************/
int max_product(const std::vector<int> &a) {
    if (a.empty()) return 0;
    int maxi = a[0], mini = a[0], max = a[0];
    for (size_t i = 1; i < a.size(); ++i) {
        int maxn = maxi * a[i];
        int minn = mini * a[i];
        maxi = std::max({ a[i], maxn, minn });
        mini = std::min({ a[i], maxn, minn });
        max = std::max(max, maxi);
    }
    return max;
}
/***********************************************************/
int booth_multiply(int a, int b) {
    return 0;
}
/***********************************************************/
uint64_t long_multiplication(uint32_t a, uint32_t b) {
    const size_t n = sizeof(uint32_t) * CHAR_BIT;
    auto av = std::bitset<n>(a), bv = std::bitset<n>(b);
    auto rv = std::bitset<2 * n>();

    uint32_t x = 0;
    for (size_t i = 0; i < 2 * n; i++) {
        size_t j0 = std::max(n, i + 1) - n;
        size_t jn = std::min(n, i + 1);

        for (size_t j = j0; j < jn; j++)
            x += av[j] & bv[i - j];

        rv[i] = x & 1;
        x >>= 1;
    }
    return rv.to_ullong();
}
/**********************************************************************/
unsigned long long find_next_number(unsigned long long n) {
    typedef unsigned short digit;
    const digit base = 10;
    digit pd = 0; // Previous digit.
    digit cd; // Current digit.
    digit count[base] = { 0 };
    decltype(n) result = n;

    // Find least significant digit that is out of order.
    while (result >= base) {
        cd = result % base;
        result /= base;
        ++count[cd];
        if (cd < pd) break;
        pd = cd;
    }
    if (cd >= pd) return n;

    // Find a digit less significant and larger than the above.
    for (++cd; count[cd] == 0; ++cd) {}

    // Append that digit to the result.
    result = result * base + cd;
    --count[cd];

    // Append remaining digits in sorted order.
    for (cd = 0; cd < base; cd++)
        while (count[cd]--) result = result * base + cd;

    return result;
}
//98725349
//int n1 = find_next_number2(98724953);
//int n2 = find_next_number2(321);
//int n3 = find_next_number2(1);
//int n4 = find_next_number2(218765);
/**********************************************************************/
/*
Given an array where each element is the money a person have and there 
is only Rs. 3 note. We need to check whether it is possible to divide 
the money equally among all the persons or not. If it is possible then 
find Minimum number of transactions needed.

8
11  4 transactions
12
13
6
*/
/**********************************************************************/
// http://www.geeksforgeeks.org/binary-indexed-tree-or-fenwick-tree-2/
std::vector<int> bit_construct(const std::vector<int> &v) {
    std::vector<int> bit(v.size() + 1, 0);
    for (size_t i = 1; i < bit.size(); ++i)
        for (size_t j = i; j < bit.size(); j += j & -(ptrdiff_t)j)
            bit[j] += v[i - 1];
    return bit;
}
int bit_sum(std::vector<int> bit, ptrdiff_t i) {
    int sum = 0;
    for (++i; i > 0; i -= i & -i) sum += bit[i];
    return sum;
}
void bit_scale(std::vector<int> &bit, int c) {
    std::transform(bit.begin(), bit.end(), 
                   bit.begin(), [c](int e) { return c * e; });
}
// http://community.topcoder.com/tc?module=Static&d1=tutorials&d2=binaryIndexedTrees
// Finds first occurrence of a sum in an sequence of numbers from its Binary Indexed Tree.
size_t find_first(std::vector<int> &bit, int sum) {
    size_t i = 0;
    size_t mask = msb_mask(bit.size() - 1);

    while (mask != 0 && i < bit.size()) {
        size_t j = i + mask;
        if (sum == bit[j]) return j - 1;
        if (sum >= bit[j]) {
            sum -= bit[j];
            i = j;
        }
        mask >>= 1;
    }
    return sum != 0 ? bit.size() : i - 1;
}
size_t find_any(std::vector<int> &bit, int sum) {
    size_t i = 0;
    size_t mask = msb_mask(bit.size() - 1);

    while (mask != 0 && i < bit.size()) {
        size_t j = i + mask;
        if (sum >= bit[j]) {
            i = j;
            sum -= bit[j];
        }
        mask >>= 1;
    }
    return sum != 0 ? bit.size() : i - 1;
}
/**********************************************************************/
// Finds the first number missing from a set of numbers in which each 
// number of a range appears exactly twice, except for one.
int find_first_missing(const std::vector<int> &a) {
    int missing = 0;
    for (int i : a) missing ^= i;
    return missing;
}
int find_first_missing(const std::vector<int> &a, const int max) {
    return max * (max + 1) - std::accumulate(a.begin(), a.end(), 0);
}
void find_first_missing() {
    const int max = 50;
    std::vector<int> v(max * 2);
    std::iota(v.begin(), v.begin() + max, 1);
    std::iota(v.begin() + max, v.end(), 1);
    v.erase(v.begin() + 10 - 1);
    int missing = find_first_missing(v);
    int missing2 = find_first_missing(v, max);
}
/**********************************************************************/