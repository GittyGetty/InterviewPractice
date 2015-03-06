#include <iostream>

#include "DynamicProgramming.h"

/*************************************************************************************/
bool can_win_print_solution(const std::vector<int> &a, int s, const std::vector<int> &m, bool t) {
    if (s <= 0) {
        std::cout << !t << " wins: ";
        for (int i : m) std::cout << i << " ";
        std::cout << std::endl;
        return !t;
    }
    if (a.empty()) {
        std::cout << "Neither wins." << std::endl;
        return false;
    }
    for (size_t i = 0; i < a.size(); ++i) {
        std::vector<int> c = a;
        c.erase(c.begin() + i);
        auto mt = m;
        mt.push_back(a[i]);
        bool b = can_win_print_solution(c, s - a[i], mt, !t);
        if (t == b) return b;
    }
    return !t;
}
// Same as above, without output.
bool can_win(const std::vector<int> &a, int s, bool t) {
    if (s <= 0) return !t;
    if (a.empty()) return false;
    for (size_t i = 0; i < a.size(); ++i) {
        std::vector<int> c = a;
        c.erase(c.begin() + i);
        bool b = can_win(c, s - a[i], !t);
        if (t == b) return b;
    }
    return !t;
}
// Without turn variable, a player can only obtain information
// about the possibility for the other player winning. If both
// players can lose, because there are not enough numbers to
// reach the sum, then the other player's loss is not enough to
// determine this player's win. With the turn variable, player
// 1 winning can be determined independently of player 2's loss.
bool will_not_lose(const std::vector<int> &a, int s) {
    if (s <= 0) return false;
    if (a.empty()) return false;
    bool lose = true;
    for (size_t i = 0; i < a.size(); ++i) {
        std::vector<int> c = a;
        c.erase(c.begin() + i);
        lose = lose && will_not_lose(c, s - a[i]);
    }
    return !lose;
}
/*************************************************************************************/
