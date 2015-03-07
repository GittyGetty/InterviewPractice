#include <algorithm>
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
// http://www.geeksforgeeks.org/find-the-minimum-cost-to-reach-a-destination-where-every-station-is-connected-in-one-direction/
#define N 4 // Train stations
int min_cost(int cost[][N], int s, int d) {
    if (s == d || s + 1 == d) return cost[s][d];
    int min = cost[s][d];
    for (int i = s + 1; i<d; i++) {
        int c = min_cost(cost, s, i) + min_cost(cost, i, d);
        min = std::min(min, c);
    }
    return min;
}
int min_cost(int cost[][N]) {
    return min_cost(cost, 0, N - 1);
}
int test_min_cost() {
    int cost[N][N] = { 
        { 0, 15, 80, 90 },
        { INT_MAX, 0, 40, 50 },
        { INT_MAX, INT_MAX, 0, 70 },
        { INT_MAX, INT_MAX, INT_MAX, 0 }
    };
    std::cout << "The Minimum cost to reach station " << N << " is " << min_cost(cost);
    return 0;
}
/*************************************************************************************/
// http://www.geeksforgeeks.org/count-number-ways-reach-given-score-game/
// Consider a game where a player can score 3 or 5 or 10 points in a move. Given a 
// total score n, find number of ways to reach the given score.
int solution_count(int n) {
    std::vector<int> moves = { 3, 5, 10 };
    std::vector<int> c(n + 1, 0);
    c[0] = 1;
    for (int m : moves) for (size_t i = m; i <= n; ++i) c[i] += c[i - m];
    return c[n];
}
void test_game_score() {
    int n;
    n = solution_count(20); // 4
    n = solution_count(13); // 2
}
/*************************************************************************************/