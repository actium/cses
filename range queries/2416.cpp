#include <algorithm>
#include <iostream>
#include <vector>

struct Query {
    unsigned a;
    unsigned b;
    unsigned long long v;
};

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    unsigned n, q;
    std::cin >> n >> q;

    std::vector<unsigned> xs(n);
    for (unsigned i = 0; i < n; ++i)
        std::cin >> xs[i];

    xs.push_back(~0u);

    std::vector<Query> qs(q);
    for (unsigned i = 0; i < q; ++i)
        std::cin >> qs[i].a >> qs[i].b;

    std::vector<unsigned long long> ps(1+n);
    for (unsigned i = 0; i < n; ++i)
        ps[i+1] = ps[i] + xs[i];

    const auto count = [&](unsigned a, unsigned b) {
        return 1ull * xs[a] * (b - a) - (ps[b] - ps[a]);
    };

    std::vector<Query*> rs(q);
    for (unsigned i = 0; i < q; ++i)
        rs[i] = &qs[i];

    std::sort(rs.begin(), rs.end(), [](const Query* lhs, const Query* rhs) {
        return lhs->a < rhs->a;
    });

    std::vector<unsigned> t;
    t.push_back(n);

    std::vector<unsigned long long> ds(n + 1);
    for (unsigned i = n-1; !rs.empty(); --i) {
        while (xs[i] > xs[t.back()])
            t.pop_back();

        ds[i] = ds[t.back()] + count(i, t.back());
        t.push_back(i);

        while (!rs.empty() && rs.back()->a == i + 1) {
            const unsigned g = rs.back()->b;

            const auto it = std::lower_bound(t.begin(), t.end(), g, [&](unsigned x, unsigned v) {
                return x > v;
            });

            rs.back()->v = ds[i] - ds[*it] + count(*it, g);
            rs.pop_back();
        }
    }

    for (unsigned i = 0; i < q; ++i)
        std::cout << qs[i].v << '\n';

    return 0;
}
