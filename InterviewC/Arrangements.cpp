#include <algorithm>
#include <vector>
#include "Arrangements.h"
/**********************************************************************/
// http://www.geeksforgeeks.org/fill-two-instances-numbers-1-n-specific-way/
// Given a number n, create an array of size 2n such that the array contains 
// two instances of every number from 1 to n, and the number of elements 
// between two instances of a number i is equal to i. If such a configuration 
// is not possible, then print the same.
bool fill(std::vector<int> &v, size_t n) {
    if (!n) return true;
    for (size_t i = 0; i < 2 * v.size() - 1 - n; ++i) {
        size_t j = i + n + 1;
        if (!v[i] && !v[j]) {
            v[i] = v[j] = n;
            if (fill(v, n - 1)) return true;
            v[i] = v[j] = 0;
        }
    }
    return false;
}
std::vector<int> fill(size_t n) {
    std::vector<int> v(2 * n, 0);
    fill(v, n);
    return v;
}
void fill_test() {
    std::vector<int> v;
    v = fill(1);
    v = fill(2);
    v = fill(3);
    v = fill(4);
    v = fill(5);
    v = fill(6);
}
/**********************************************************************/
// http://www.geeksforgeeks.org/check-if-array-elements-are-consecutive/
// Assume all numbers are greater than zero.
bool are_consecutive(std::vector<int> &v) {
    int max = v[0], min = v[0];
    for (int i : v) {
        max = std::max(max, i);
        min = std::min(min, i);
    }
    if (max - min  + 1 > v.size()) return false;
    for (size_t i = 0; i < v.size(); i++) v[std::abs(v[i]) - min] *= -1;
    for (int i : v) if (i > 0) return false;
    return true;
}
void are_consecutive_test() {
    bool b;
    std::vector<int> v;
    v = { 5, 6, 7, 8 };
    b = are_consecutive(v);
    v = { 5, 6, 7, 9 };
    b = are_consecutive(v);
    v = { 5, 1, 2, 8 };
    b = are_consecutive(v);
    v = { 3, 1, 5, 2, 4 };
    b = are_consecutive(v);
}
/**********************************************************************/