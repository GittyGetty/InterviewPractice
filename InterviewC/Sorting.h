#include <vector>

void counting_sort(int* a, size_t n, size_t k);

void sift_down_max(std::vector<int> &a, size_t start, size_t end);
void make_max_heap(std::vector<int> &a);
void heap_sort(std::vector<int> &a);
int extract_max(std::vector<int> &a);
void bubble_sort(std::vector<int> &a);
void straight_insertion_sort(std::vector<int> &v);
void test_select_k();
void median_of_medians_test();
void group_duplicates_test();