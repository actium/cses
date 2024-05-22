#include <algorithm>
#include <iostream>
#include <map>
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

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    unsigned n, q;
    std::cin >> n >> q;

    std::vector<unsigned> xs(n);
    for (unsigned i = 0; i < n; ++i)
        std::cin >> xs[i];

    std::vector<unsigned> as(q), bs(q);
    for (unsigned i = 0; i < q; ++i)
        std::cin >> as[i] >> bs[i];

    std::vector<std::pair<unsigned, unsigned>> p(q);
    for (unsigned i = 0; i < q; ++i)
        p[i].first = i;

    std::sort(p.begin(), p.end(), [&](const auto& lhs, const auto& rhs) {
        return bs[lhs.first] < bs[rhs.first];
    });

    BinaryIndexedTree<int> bit(n + 1);
    std::map<unsigned, unsigned> vs;
    for (unsigned i = 0, j = 0; i < n; ++i) {
        if (const auto it = vs.find(xs[i]); it != vs.end())
            bit.update(it->second, -1);

        vs[xs[i]] = i;
        bit.update(i, 1);

        while (j < q && bs[p[j].first] == i + 1) {
            p[j].second = bit.sum(as[p[j].first] - 1, i + 1);
            ++j;
        }
    }

    std::sort(p.begin(), p.end());

    for (unsigned i = 0; i < q; ++i)
        std::cout << p[i].second << '\n';

    return 0;
}
