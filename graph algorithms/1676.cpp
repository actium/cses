#include <iostream>
#include <utility>
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

    unsigned size(unsigned x) noexcept
    {
        return -data_[locate(x)];
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

    void unite(unsigned u, unsigned v)
    {
        unsigned ru = locate(u), rv = locate(v);
        if (ru == rv)
            return;

        if (data_[ru] > data_[rv])
            std::swap(ru, rv);

        data_[ru] += data_[rv];
        data_[rv] = ru;
        --size_;
    }

private:
    unsigned size_;

    std::vector<int> data_;

}; // class DisjointSetUnion

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    unsigned n, m;
    std::cin >> n >> m;

    DisjointSetUnion dsu(n);
    for (unsigned i = 0, k = 1; i < m; ++i) {
        unsigned s, t;
        std::cin >> s >> t;

        dsu.unite(s-1, t-1);
        k = std::max(k, dsu.size(s-1));

        std::cout << dsu.size() << ' ' << k << '\n';
    }

    return 0;
}
