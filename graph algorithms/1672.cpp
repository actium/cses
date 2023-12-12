#include <iostream>
#include <vector>

using integer = unsigned long long;

constexpr integer oo = ~0ull >> 4;

int main()
{
    unsigned n, m, q;
    std::cin >> n >> m >> q;

    std::vector<std::vector<integer>> distances(1+n, std::vector<integer>(1+n, oo));
    for (unsigned i = 1; i <= n; ++i)
        distances[i][i] = 0;

    for (unsigned i = 0; i < m; ++i) {
        unsigned a, b, c;
        std::cin >> a >> b >> c;

        distances[a][b] = std::min<integer>(distances[a][b], c);
        distances[b][a] = std::min<integer>(distances[b][a], c);
    }

    for (unsigned i = 1; i <= n; ++i) {
        for (unsigned j = 1; j <= n; ++j) {
            for (unsigned k = 1; k <= n; ++k)
                distances[j][k] = std::min(distances[j][k], distances[j][i] + distances[i][k]);
        }
    }

    for (unsigned i = 0; i < q; ++i) {
        unsigned a, b;
        std::cin >> a >> b;

        const integer d = distances[a][b];
        if (d == oo)
            std::cout << -1 << '\n';
        else
            std::cout << d << '\n';
    }

    return 0;
}
