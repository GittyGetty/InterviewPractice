#include <cstdio>
#include <memory>

#include "Sorting.h"

/*************************************************************************************/
void counting_sort(int* a, size_t n, size_t k) {
    size_t* count = new size_t[k];
    memset(count, 0, sizeof(size_t) * k);

    for (size_t i = 0; i < n; i++) count[a[i] - 1]++;

    int sum = 0;
    for (size_t i = 0; i < k; i++) {
        int tmp = count[i];
        count[i] = sum;
        sum += tmp;
    }

    int* result = new int[n];
    for (size_t i = 0; i < n; i++) {
        result[count[a[i] - 1]] = a[i];
        count[a[i]]++;
    }

    for (size_t i = 0; i < n; i++) {
        printf("%d\n", result[i]);
    }
}
/*************************************************************************************/
typedef std::vector<int>::size_type vsize;
void sift_down(std::vector<int> &v, vsize start, vsize end) {
    vsize in = start;
    while (2 * in + 1 < end) {
        vsize il = 2 * in + 1, ir = il + 1, imax = in;
        if (v[il] > v[imax]) imax = il;
        if (ir < end && v[ir] > v[imax]) imax = ir;
        if (imax == in) return;
        std::swap(v[in], v[imax]);
        in = imax;
    }
}
int extract_max(std::vector<int> &a) {
    int result = a[0];
    std::swap(a[0], a[a.size() - 1]);
    a.pop_back();
    sift_down(a, 0, a.size());
    return result;
}
void heapify(std::vector<int> &v) {
    for (ptrdiff_t start = v.size() / 2 - 1; start >= 0; --start)
        sift_down(v, start, v.size());
}
void heap_sort(std::vector<int> &v) {
    heapify(v);
    for (vsize end = v.size() - 1; end >= 1; --end) {
        std::swap(v[0], v[end]);
        sift_down(v, 0, end);
    }
}
/*************************************************************************************/
void bubble_sort(std::vector<int> &a) {
    for (size_t i = 1; i < a.size(); ++i)
        for (size_t j = i; j > 0 && a[j - 1] > a[j]; --j) 
            std::swap(a[j], a[j - 1]);
}
/*************************************************************************************/
void straight_insertion_sort(std::vector<int> &v) {
    for (size_t i = 1; i < v.size(); ++i) {
        int t = v[i];
        size_t j;
        for (j = i; j > 0 && v[j - 1] > t; --j) v[j] = v[j - 1];
        v[j] = t;
    }
}
/*************************************************************************************/