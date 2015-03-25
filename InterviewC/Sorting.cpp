#include <algorithm>
#include <cstdio>
#include <functional>
#include <iterator>
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
// This one uses a slightly harder to understand partitioning algorithm.
int select_k(std::vector<int> &v, int k) {
    if ((size_t)k >= v.size()) return -1;
    int l = 0, r = v.size() - 1; // left/right
    while (l < r) { // l and r will converge around k
        int lp = l, rp = r; // left/right of partition
        int pivot = v[(lp + rp) / 2];
        while (lp < rp) {
            if (v[lp] >= pivot) std::swap(v[lp], v[rp--]);
            else lp++;
        }
        if (v[lp] > pivot) lp--;
        // Here: v[i] <= pivot, for all i <= lp.
        if (k > lp) l = lp + 1;
        else r = lp;
    }
    return v[k];
}
// This one uses a simpler to understand partitioning algorithm.
int qselect(std::vector<int> &v, size_t k) {
    size_t l = 0, r = v.size() - 1;
    while (l < r) {
        size_t lt, gt;
        for (gt = lt = l; lt < r; lt++) {
            if (v[lt] <= v[r])
                std::swap(v[lt], v[gt++]);
        }
        std::swap(v[r], v[gt]); // [l..gt] <= pivot
        int p = v[gt];
        if (gt == k) break;
        if (k < gt) r = gt - 1;
        if (k > gt) l = gt + 1;
    }
    return v[k];
}
// Same as above, but returns duplicate elements..
std::vector<int> multi_qselect(std::vector<int> &v, size_t k) {
    size_t l = 0, r = v.size() - 1;
    while (l < r) {
        size_t lt, gt;
        for (gt = lt = l; lt < r; lt++)
            if (v[lt] <= v[r])
                std::swap(v[lt], v[gt++]);
        std::swap(v[r], v[gt]);
        if (k <= gt) r = gt - 1;
        if (k > gt) l = gt + 1;
    }
    std::vector<int> res;
    for (size_t i = k; i <= k && v[i] == v[k]; --i)
        if (v[i] == v[k]) res.push_back(v[i]);
    for (size_t i = k + 1; i < v.size() && v[i] == v[k]; ++i)
        if (v[i] == v[k]) res.push_back(v[i]);
    return res;
}
void test_select_k() {
    int r;
    std::vector<int> v, res;

    v = { 100, 1, 2, 3, 100 };
    res = multi_qselect(v, 4);

    v = { 100, 1, 2, 3, 100, 4, 100, 5 };
    res = multi_qselect(v, 6);

    v = { 1, 1, 2, 3, 4, 5, 5, 6, 7, 100 };
    res = multi_qselect(v, 9);

    // Single select.
    v = { 2, 1, 0, 1, 0, 1, 0, };
    r = qselect(v, 3);

    // Multi select.
    //    0  1  2  3  4   5  6   7  8  9 10 11 12 13
    //   -1,-1, 0, 1, 2,  3, 4,  5, 5, 6, 7, 8, 8, 9 
    v = { 3, 4, 8, 6, 7, -1, 1, -1, 5, 8, 0, 2, 5, 9 };
    res = multi_qselect(v, 0);
    res = multi_qselect(v, 1);
    res = multi_qselect(v, 2);
    res = multi_qselect(v, 3);
    res = multi_qselect(v, 4);
    res = multi_qselect(v, 5);
    res = multi_qselect(v, 11);
}
/*************************************************************************************/
// https://yiqi2.wordpress.com/2013/07/03/median-of-medians-selection-algorithm/
// Not working. Abandoning for now, because it is too long for an interview anyway.
// Just note that this is the general approach of performing an O(n) selection 
// algorithm.
int mom(std::vector<int> &a, int s, int n, int k) {
    if (n == 1 && k == 1) return a[s];
    int m = (n + 4) / 5;
    std::vector<int> mid(m);
    for (int i = 0; i < m; i++) {
        int t = s + i * 5;
        if (n - t > 4) {
            std::sort(&a[t], &a[t + 5 - 1]);
            mid[i] = a[t + 2];
        }
        else {
            std::sort(&a[t], &a[n - t - 1]);
            mid[i] = a[t + (n - t - 1) / 2];
        }
    }
    int pivot = mom(mid, 0, m, (m + 1) / 2);
    for (int i = 0; i < n; i++) {
        if (a[s + i] == pivot) {
            std::swap(a[s + i], a[s + n - 1]);
            break;
        }
    }
    int pos = 0;
    for (int i = 0; i < n - 1; i++) {
        if (a[s + i] < pivot) {
            if (i != pos) std::swap(a[s + i], a[s + pos]);
            pos++;
        }
    }
    std::swap(a[s + pos], a[s + n - 1]);
    if (pos == k - 1) return pivot;
    if (pos > k - 1) return mom(a, s, pos, k);
    return mom(a, s + pos + 1, n - pos - 1, k - pos - 1);
}
void median_of_medians_test() {
    std::vector<int> v;
    int res;

    v = { 100, 1, 2, 3, 100 };
    res = mom(v, 0, v.size(), 3);
    v = { 100, 1, 2, 3, 100, 4, 100, 4 };
    res = mom(v, 0, v.size(), 5);
    v = { 1, 1, 2, 3, 4, 5, 5, 6, 7, 100 };
    res = mom(v, 0, v.size(), 5);
}
/*************************************************************************************/