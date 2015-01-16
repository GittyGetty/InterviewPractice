#include <string>
#include <iostream>
#include <cstdio>
#include <vector>
#include <set>
#include <memory>

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
std::set<std::wstring> longest_common_substrings(std::wstring sa, std::wstring sb) {
    auto prefixes = std::unique_ptr<ussize[]>(new ussize[sa.size()]);
    for (size_t i = 0; i < sa.size(); ++i)
        prefixes[i] = ussize(new ssize[sb.size()]);

    std::set<std::wstring> result;
    ssize longest = 0;

    for (ssize a = 0; a < sa.size(); ++a) {
        for (ssize b = 0; b < sb.size(); ++b) {
            if      (sa[a] != sb[b])   prefixes[a][b] = 0;
            else if (a == 0 || b == 0) prefixes[a][b] = 1;
            else                       prefixes[a][b] = prefixes[a - 1][b - 1] + 1;

            if (prefixes[a][b] < longest) continue;
            if (prefixes[a][b] > longest) {
                longest = prefixes[a][b];
                result.clear();
            }
            auto sub = sa.substr(a - longest + 1, longest);
            result.insert(sub);
        }
    }
    return result;
}
/************************************************************************/
