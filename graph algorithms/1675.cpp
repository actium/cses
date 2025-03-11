#include <algorithm>
#include <iostream>
#include <vector>

class DisjointSetUnion {
public:
    explicit DisjointSetUnion(unsigned size)
        : size_(size)
        , data_(size, -1)
    {}

    unsigned size() const noexcept
    {
        return size_;
    }

    unsigned locate(unsigned x) noexcept
    {
        unsigned rx = x;
        while (data_[rx] >= 0)
            rx = data_[rx];

        while (data_[x] >= 0)
            x = std::exchange(data_[x], rx);

        return rx;
    }

    bool unite(unsigned u, unsigned v)
    {
        unsigned ru = locate(u), rv = locate(v);
        if (ru == rv)
            return false;

        if (data_[ru] > data_[rv])
            std::swap(ru, rv);

        data_[ru] += data_[rv];
        data_[rv] = ru;
        --size_;

        return true;
    }

private:
    unsigned size_;

    std::vector<int> data_;

}; // class DisjointSetUnion

struct Edge {
    unsigned s;
    unsigned t;
    unsigned w;
};

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    unsigned n, m;
    std::cin >> n >> m;

    std::vector<Edge> edges(m);
    for (unsigned i = 0; i < m; ++i)
        std::cin >> edges[i].s >> edges[i].t >> edges[i].w;

    std::sort(edges.begin(), edges.end(), [](const Edge& lhs, const Edge& rhs) {
        return lhs.w < rhs.w;
    });

    DisjointSetUnion dsu(n);
    unsigned long long w = 0;
    for (const Edge& e : edges) {
        if (dsu.unite(e.s-1, e.t-1))
            w += e.w;
    }

    if (dsu.size() == 1)
        std::cout << w << '\n';
    else
        std::cout << "IMPOSSIBLE" << '\n';

    return 0;
}
