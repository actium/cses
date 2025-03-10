#include <iostream>
#include <set>
#include <vector>

using integer = unsigned long long;
using graph_t = std::vector<std::vector<std::pair<unsigned, unsigned>>>;

constexpr integer oo = ~integer(0);

struct State {
    unsigned node;
    integer cost;
    bool coupon_used;
};

bool operator <(const State& lhs, const State& rhs)
{
    if (lhs.cost != rhs.cost)
        return lhs.cost < rhs.cost;

    return lhs.coupon_used != rhs.coupon_used ? lhs.coupon_used > rhs.coupon_used : lhs.node < rhs.node;
}

integer solve(const graph_t& g)
{
    const unsigned n = g.size();

    std::vector<integer> d[2];
    for (unsigned i = 0; i < 2; ++i)
        d[i].resize(n, oo);

    std::set<State> q;

    const auto enqueue = [&](unsigned u, integer w, bool c) {
        if (w < d[c][u]) {
            q.erase(State { u, d[c][u], c });
            d[c][u] = w;
            q.insert(State { u, d[c][u], c });
        }
    };

    enqueue(0, 0, false);
    while (q.begin()->node != n-1) {
        const State x = *q.begin();
        q.erase(q.begin());

        for (const std::pair<unsigned, unsigned>& e : g[x.node]) {
            if (!x.coupon_used)
                enqueue(e.first, x.cost + e.second / 2, true);

            enqueue(e.first, x.cost + e.second, x.coupon_used);
        }
    }

    return q.begin()->cost;
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    unsigned n, m;
    std::cin >> n >> m;

    graph_t g(n);
    for (unsigned i = 0; i < m; ++i) {
        unsigned s, t, w;
        std::cin >> s >> t >> w;

        g[s-1].emplace_back(t-1, w);
    }

    std::cout << solve(g) << '\n';

    return 0;
}
