#include <iostream>
#include <set>
#include <vector>

void solve(const std::vector<unsigned>& xs, unsigned k)
{
    const unsigned n = xs.size();

    if (k == 1) {
        for (unsigned i = 0; i < n; ++i)
            std::cout << 0 << ' ';

        return;
    }

    std::multiset<unsigned> s[2];
    for (unsigned i = 0; i < k; ++i)
        s[0].insert(xs[i]);

    while (2 * s[0].size() > k + 1) {
        s[1].insert(*s[0].rbegin());
        s[0].erase(std::prev(s[0].end()));
    }

    unsigned long long c = 0;

    unsigned m = *s[0].rbegin();
    for (unsigned i = 0; i < k; ++i)
        c += abs(xs[i] - m);

    std::cout << c;

    for (unsigned i = k; i < n; ++i) {
        const unsigned q = xs[i-k];
        if (q < *s[1].begin()) {
            s[0].erase(s[0].find(q));
            s[0].insert(xs[i]);
        } else {
            s[1].erase(s[1].find(q));
            s[1].insert(xs[i]);
        }

        c -= abs(q - m);

        while (*s[0].rbegin() > *s[1].begin()) {
            const unsigned u = *s[0].rbegin(), v = *s[1].begin();
            s[0].erase(std::prev(s[0].end()));
            s[1].erase(s[1].begin());
            s[0].insert(v);
            s[1].insert(u);
        }

        const unsigned d = abs(*s[0].rbegin() - m);
        if (*s[0].rbegin() < m)
            c += (s[1].size() - s[0].size() + 1ull) * d;
        if (*s[0].rbegin() > m)
            c += (s[0].size() - s[1].size() - 1ull) * d;

        m = *s[0].rbegin();
        c += abs(xs[i] - m);

        std::cout << ' ' << c;
    }
}

int main()
{
    unsigned n, k;
    std::cin >> n >> k;

    std::vector<unsigned> xs(n);
    for (unsigned i = 0; i < n; ++i)
        std::cin >> xs[i];

    solve(xs, k);

    return 0;
}
