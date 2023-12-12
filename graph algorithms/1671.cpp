#include <iostream>
#include <set>
#include <vector>

constexpr unsigned long long oo = ~0ull;

struct Flight {
    unsigned b;
    unsigned c;
};

int main()
{
    unsigned n, m;
    std::cin >> n >> m;

    std::vector<std::vector<Flight>> fs(1 + n);
    for (unsigned i = 0; i < m; ++i) {
        unsigned a, b, c;
        std::cin >> a >> b >> c;

        fs[a].push_back({ b, c });
    }

    std::vector<unsigned long long> p(1 + n, oo);

    std::set<std::pair<unsigned long long, unsigned>> q;
    q.emplace(0, 1);
    while (!q.empty()) {
        const auto u = *q.begin();
        q.erase(q.begin());

        if (p[u.second] != oo)
            continue;

        p[u.second] = u.first;

        for (const auto& x : fs[u.second]) {
            if (p[x.b] == oo)
                q.emplace(u.first + x.c, x.b);
        }
    }

    for (unsigned i = 1; i <= n; ++i)
        std::cout << p[i] << ' ';

    return 0;
}
