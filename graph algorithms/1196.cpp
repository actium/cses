#include <iostream>
#include <set>
#include <vector>

using graph_t = std::vector<std::vector<std::pair<unsigned, unsigned>>>;

void solve(const graph_t& g, unsigned k)
{
    using integer = unsigned long long;

    const unsigned n = g.size();

    std::multiset<std::pair<integer, unsigned>> q;
    std::vector<unsigned> c(n);

    q.emplace(0, 0);
    for (unsigned r = k; r != 0; ) {
        const std::pair<integer, unsigned> x = *q.begin();
        q.erase(q.begin());

        if (++c[x.second] > k)
            continue;

        for (const std::pair<unsigned, unsigned>& e : g[x.second])
            q.emplace(x.first + e.second, e.first);

        if (x.second == n-1) {
            std::cout << x.first << ' ';
            --r;
        }
    }
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    unsigned n, m, k;
    std::cin >> n >> m >> k;

    graph_t g(n);
    for (unsigned i = 0; i < m; ++i) {
        unsigned s, t, w;
        std::cin >> s >> t >> w;

        g[s-1].emplace_back(t-1, w);
    }

    solve(g, k);

    return 0;
}
