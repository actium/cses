#include <iostream>
#include <vector>

void visit(const std::vector<std::vector<unsigned>>& adjacents, unsigned u, std::vector<bool>& v)
{
    v[u] = true;

    for (const unsigned x : adjacents[u]) {
        if (!v[x])
            visit(adjacents, x, v);
    }
}

int main()
{
    unsigned n, m;
    std::cin >> n >> m;

    std::vector<std::vector<unsigned>> adjacents(1 + n);
    for (unsigned i = 0; i < m; ++i) {
        unsigned a, b;
        std::cin >> a >> b;

        adjacents[a].push_back(b);
        adjacents[b].push_back(a);
    }

    std::vector<unsigned> r;

    std::vector<bool> v(1 + n);
    for (unsigned i = 1; i <= n; ++i) {
        if (!v[i]) {
            r.push_back(i);
            visit(adjacents, i, v);
        }
    }

    const unsigned k = r.size();

    std::cout << k - 1 << '\n';
    for (unsigned i = 1; i < k; ++i)
        std::cout << 1 << ' ' << r[i] << '\n';

    return 0;
}
