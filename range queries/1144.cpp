#include <algorithm>
#include <iostream>
#include <vector>

template <typename T>
class BinaryIndexedTree {
public:
    explicit BinaryIndexedTree(unsigned size)
        : nodes_(1 + size)
    {}

    template <typename U>
    void update(unsigned index, U delta)
    {
        for (++index; index < nodes_.size(); index += index & -index)
            nodes_[index] += delta;
    }

    T sum(unsigned range_begin, unsigned range_end) const
    {
        auto sum = T();
        while (range_end > range_begin) {
            sum += nodes_[range_end];
            range_end &= range_end - 1;
        }
        while (range_begin > range_end) {
            sum -= nodes_[range_begin];
            range_begin &= range_begin - 1;
        }
        return sum;
    }

private:
    std::vector<T> nodes_;

}; // class BinaryIndexedTree<T>

struct Query {
    char t;
    union {
        struct {
            unsigned k;
            unsigned x;
        };
        struct {
            unsigned a;
            unsigned b;
        };
    };
};

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    unsigned n, q;
    std::cin >> n >> q;

    std::vector<unsigned> ps(n);
    for (unsigned i = 0; i < n; ++i)
        std::cin >> ps[i];

    std::vector<Query> qs(q);
    for (unsigned i = 0; i < q; ++i)
        std::cin >> qs[i].t >> qs[i].a >> qs[i].b;

    std::vector<unsigned> vs(ps.begin(), ps.end());
    for (unsigned i = 0; i < q; ++i) {
        if (qs[i].t == '!')
            vs.push_back(qs[i].x);
    }

    std::sort(vs.begin(), vs.end());
    vs.erase(std::unique(vs.begin(), vs.end()), vs.end());

    const auto index = [&](unsigned v) {
        return std::lower_bound(vs.begin(), vs.end(), v) - vs.begin();
    };

    BinaryIndexedTree<unsigned> bit(vs.size());
    for (unsigned i = 0; i < n; ++i)
        bit.update(index(ps[i]), +1);

    for (unsigned i = 0; i < q; ++i) {
        if (qs[i].t == '!') {
            bit.update(index(ps[qs[i].k-1]), -1);
            ps[qs[i].k-1] = qs[i].x;
            bit.update(index(ps[qs[i].k-1]), +1);
        } else {
            std::cout << bit.sum(index(qs[i].a), index(qs[i].b + 1)) << '\n';
        }
    }

    return 0;
}
