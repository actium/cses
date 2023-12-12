#include <iostream>
#include <vector>

bool search(const std::vector<std::vector<unsigned>>& adjacents, unsigned u, unsigned s, std::vector<unsigned>& p)
{
    const unsigned n = adjacents.size();

    p[u] = s;

    for (const unsigned x : adjacents[u]) {
        if (x == s)
            continue;

        if (p[x] != n) {
            std::vector<unsigned> path = { x };
            while (u != x) {
                path.push_back(u);
                u = p[u];
            }
            path.push_back(x);

            std::cout << path.size() << '\n';
            for (const unsigned x : path)
                std::cout << x << ' ';

            return true;
        }

        if (search(adjacents, x, u, p))
            return true;
    }

    return false;
}

void solve(const std::vector<std::vector<unsigned>>& adjacents)
{
    const unsigned n = adjacents.size();

    std::vector<unsigned> p(n, n);
    for (unsigned i = 1; i < n; ++i) {
        if (p[i] == n && search(adjacents, i, i, p))
            return;
    }

    std::cout << "IMPOSSIBLE";
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

    solve(adjacents);

    return 0;
}
