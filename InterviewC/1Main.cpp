#include <fstream>
#include <vector>
#include <cstdint>
#include <set>
#include <memory>
#include <ctime>
#include <iostream>
#include <cassert>
#include <string>
#include <numeric>

#include "Arithmetic.h"
#include "BinaryTrees.h"
#include "Permutations.h"
#include "Sorting.h"
#include "String.h"

#include <stdio.h>
#define TOTAL_ELEMENTS (sizeof(array) / sizeof(array[0]))
int array[] = { 23, 34, 12, 17, 204, 99, 16 };

int main() {
    int d = TOTAL_ELEMENTS;
    for (d = -1; d <= ((ptrdiff_t)TOTAL_ELEMENTS - 2); d++)
        printf("%d\n", array[d + 1]);

    using namespace BinaryTrees;

    std::vector<int> v = { 1, 2, 3, 4, 6, 5, 7, 8 };
    straight_insertion_sort(v);

    bool b;
    b = is_rotation(L"stackoverflow", L"tackoverflows");
    b = is_rotation(L"stackoverflow", L"ackoverflowst");
    b = is_rotation(L"stackoverflow", L"overflowstack");
    b = is_rotation(L"stackoverflow", L"stackoverflwo");

    if (printf("asdfadf"), false) {}
}