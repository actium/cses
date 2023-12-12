#include <iostream>
#include <vector>

void solve(const std::vector<std::vector<unsigned>>& adjacents)
{
    const unsigned n = adjacents.size();

    std::vector<unsigned> p(n), q;

    const auto enqueue = [&](unsigned x, unsigned s) {
        if (p[x] == 0) {
            q.push_back(x);
            p[x] = s;
        }
    };

    enqueue(1, 1);
    for (unsigned i = 0; i < q.size(); ++i) {
        unsigned u = q[i];
        if (u == n - 1) {
            std::vector<unsigned> r;
            for (p[1] = 0; u != 0; u = p[u])
                r.push_back(u);

            std::cout << r.size() << '\n';
            for (auto it = r.rbegin(); it != r.rend(); ++it)
                std::cout << *it << ' ';

            return;
        }

        for (const unsigned x : adjacents[u])
            enqueue(x, u);
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
