#include <iostream>
#include <vector>

using graph_t = std::vector<std::vector<size_t>>;

struct Node {
    unsigned candidates[2] = {};
    unsigned best = 0;
};

void traverse_1(const graph_t& g, size_t u, size_t p, std::vector<Node>& v)
{
    for (const size_t x : g[u]) {
        if (x != p) {
            traverse_1(g, x, u, v);

            v[u].candidates[1] = std::max(v[u].candidates[1], v[x].candidates[0] + 1);
            if (v[u].candidates[1] > v[u].candidates[0])
                std::swap(v[u].candidates[0], v[u].candidates[1]);
        }
    }
}

void traverse_2(const graph_t& g, size_t u, size_t p, unsigned d, std::vector<Node>& v)
{
    v[u].best = std::max(v[u].candidates[0], d);

    for (const size_t x : g[u]) {
        if (x != p) {
            const size_t i = (v[x].candidates[0] + 1 == v[u].candidates[0]);
            traverse_2(g, x, u, std::max(v[u].candidates[i], d) + 1, v);
        }
    }
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    unsigned n;
    std::cin >> n;

    graph_t g(n);
    for (size_t i = 0; i < n-1; ++i) {
        unsigned u, v;
        std::cin >> u >> v;

        g[u-1].push_back(v-1);
        g[v-1].push_back(u-1);
    }

    std::vector<Node> v(n);
    traverse_1(g, 0, 0, v);
    traverse_2(g, 0, 0, 0, v);

    for (size_t i = 0; i < n; ++i)
        std::cout << v[i].best << ' ';

    return 0;
}
