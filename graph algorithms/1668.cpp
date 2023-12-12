#include <iostream>
#include <vector>

bool paint(const std::vector<std::vector<unsigned>>& adjacents, unsigned u, unsigned c, std::vector<unsigned>& t)
{
    t[u] = c;

    for (const unsigned x : adjacents[u]) {
        if (t[x] != 0 && t[x] + c != 3)
            return false;

        if (t[x] == 0 && !paint(adjacents, x, 3-c, t))
            return false;
    }

    return true;
}

void solve(const std::vector<std::vector<unsigned>>& adjacents)
{
    const unsigned n = adjacents.size();

    std::vector<unsigned> t(n);
    for (unsigned i = 1; i < n; ++i) {
        if (t[i] == 0 && !paint(adjacents, i, 1, t)) {
            std::cout << "IMPOSSIBLE";
            return;
        }
    }

    for (unsigned i = 1; i < n; ++i)
        std::cout << t[i] << ' ';
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
