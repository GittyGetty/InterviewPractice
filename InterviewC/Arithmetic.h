#include <vector>
#include <tuple>

std::tuple<size_t, size_t> find_sub_with_sum(const std::vector<unsigned> &a, unsigned s);
int bit_sum(std::vector<int> bit, ptrdiff_t index);
void bit_update(std::vector<int> &bit, size_t index, int val);
std::vector<int> bit_construct(const std::vector<int> &v);
long sum_numbers_stl(const std::vector<int> &a);
long sum_numbers(const std::vector<int> &a);