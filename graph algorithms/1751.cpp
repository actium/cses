#include <iostream>
#include <vector>

constexpr unsigned oo = ~0u >> 1;

unsigned traverse(const std::vector<unsigned>& ts, unsigned u, unsigned d, std::vector<unsigned>& cs)
{
    const unsigned n = ts.size();

    if (cs[u] == 0) {
        cs[u] = d;

        const unsigned x = traverse(ts, ts[u], d + 1, cs);
        if (x != n) {
            cs[u] = cs[x];
            return u == x ? n : x;
        }

        cs[u] = cs[ts[u]] + 1;
        return n;
    }

    if (cs[u] >= oo) {
        cs[u] = d - cs[u];
        return u;
    }

    return n;
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    unsigned n;
    std::cin >> n;

    std::vector<unsigned> ts(1+n);
    for (unsigned i = 1; i <= n; ++i)
        std::cin >> ts[i];

    std::vector<unsigned> cs(1+n);
    for (unsigned i = 1; i <= n; ++i) {
        if (cs[i] == 0)
            traverse(ts, i, oo, cs);
    }

    for (unsigned i = 1; i <= n; ++i)
        std::cout << cs[i] << ' ';

    return 0;
}
