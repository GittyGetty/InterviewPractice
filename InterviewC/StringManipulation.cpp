#include <array>
#include <string>
#include <iostream>
#include <cstdio>
#include <vector>
#include <set>
#include <memory>
#include <algorithm>
#include <cmath>
#include <stack>

/************************************************************************/

// Print the reverse of a string using recursion.
void print_reverse(std::wstring s) {
    if (s.size() == 0) return;
    printf("%c", s[s.size() - 1]);
    s = s.substr(0, s.size() - 1);
    print_reverse(s);
}

void print_reverse_test() {
    print_reverse(L"ABCDEF");
}

/************************************************************************/

void string_matcher(const char *s, size_t ss, const char *p, size_t ps) {
    unsigned long long lp['z' - 'a' + 1] = { 0 };

    for (size_t i = 0; i < ps; i++) lp[p[i] - 'a'] |= 1ULL << i;

    unsigned long long col = s[0] == p[0];

    for (size_t i = 1; i < ss; i++) {
        if (col & 1ULL << (ps - 1))
            printf("Match @ %zu\n", i + 1 - ps);
        col = (col << 1 | 1) & lp[s[i] - 'a'];
    }

    if (col & 1ULL << (ps - 1))
        printf("Match @ %zu\n", ss - ps + 1);
}

/************************************************************************/

typedef std::wstring::size_type ssize;
typedef std::unique_ptr<ssize[]> ussize;
std::vector<std::wstring> longest_common_substrings(std::wstring sa, std::wstring sb) {
    auto prefixes = std::unique_ptr<ussize[]>(new ussize[sa.size()]);
    for (size_t i = 0; i < sa.size(); ++i)
        prefixes[i] = ussize(new ssize[sb.size()]);

    std::vector<std::wstring> result;
    ssize longest = 0;

    for (ssize a = 0; a < sa.size(); ++a) {
        for (ssize b = 0; b < sb.size(); ++b) {
            if (sa[a] != sb[b])   prefixes[a][b] = 0;
            else if (a == 0 || b == 0) prefixes[a][b] = 1;
            else                       prefixes[a][b] = prefixes[a - 1][b - 1] + 1;

            if (prefixes[a][b] < longest) continue;
            if (prefixes[a][b] > longest) {
                longest = prefixes[a][b];
                result.clear();
            }
            auto sub = sa.substr(a - longest + 1, longest);
            result.push_back(sub);
        }
    }
    return result;
}
/************************************************************************/

std::wstring longest_common_substring(std::wstring sa, std::wstring sb) {
    typedef std::wstring::size_type ssize;
    typedef std::unique_ptr<ssize[]> ussize;

    auto prefixes = std::unique_ptr<ussize[]>(new ussize[sa.size()]);
    for (size_t i = 0; i < sa.size(); ++i)
        prefixes[i] = ussize(new ssize[sb.size()]);

    std::wstring longest;

    for (ssize a = 0; a < sa.size(); ++a) {
        for (ssize b = 0; b < sb.size(); ++b) {
            if (sa[a] != sb[b])        prefixes[a][b] = 0;
            else if (a == 0 || b == 0) prefixes[a][b] = 1;
            else                       prefixes[a][b] = prefixes[a - 1][b - 1] + 1;

            if (prefixes[a][b] <= longest.size()) continue;
            longest = sa.substr(a - prefixes[a][b] + 1, prefixes[a][b]);
        }
    }
    return longest;
}

/************************************************************************/

std::wstring longest_palindrome2(std::wstring s) {
    if (s.size() == 0) return L"";

    typedef std::wstring::size_type ssize;
    typedef std::unique_ptr<bool[]> ubool;
    typedef std::unique_ptr<ubool[]> uubool;

    ssize longest_length = 1;
    ssize longest_start = 0;

    ssize n = s.size();
    auto is_palindrome = uubool(new ubool[n]);
    for (ssize i = 0; i < n; ++i) {
        is_palindrome[i] = ubool(new bool[n]);
        for (ssize j = 0; j < n; ++j) {
            is_palindrome[i][j] = i == j;

            if (std::abs((long)(i - j)) == 1 && s[i] == s[j]) {
                longest_length = 2;
                longest_start = std::min(i, j);
                is_palindrome[i][j] = true;
            }
        }
    }

    for (ssize pl = 3; pl <= n; ++pl) { // Palindrome length.
        for (ssize ps = 0; ps < n - pl; ps++) { // Palindrome start.
            ssize pe = ps + pl - 1; // Palindrome end.
            if (is_palindrome[ps + 1][pe - 1] && s[ps] == s[pe]) {
                is_palindrome[ps][pe] = true;
                longest_length = pl;
                longest_start = ps;
            }
        }
    }

    return s.substr(longest_start, longest_length);
}

/******************************************************************/

bool is_balanced(std::wstring s) {
    typedef std::wstring::size_type ssize;
    ssize balance = 0;
    for (ssize c = 0; c < s.size(); c++) {
        // Type cannot overflow since it's large enough to count
        // for a whole string consisting of opening braces.
        if (s[c] == '(') balance++;
        if (s[c] == ')') {
            // But it can underflow. It's important to check before 
            // decrement.
            if (balance == 0) return false; 
            balance--;
        }
    }
    return balance == 0;
}

/******************************************************************/
bool are_parentheses_balanced(std::string exp) {
    std::stack<char> stack;
    std::string ps = "(){}[]"; // Parentheses.

    for (std::string::size_type c = 0; c < exp.size(); ++c) {
        auto idx = ps.find(exp[c]);
        if (idx == -1) continue;
        if (idx % 2 == 0) stack.push(exp[c]);
        if (idx % 2 == 1) {
            bool unbalanced = stack.empty() || ps[idx - 1] != stack.top();
            if (unbalanced) return false;
            stack.pop();
        }
    }
    return stack.size() == 0;
}
