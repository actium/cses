#include <iostream>
#include <vector>

template <typename T>
class BinaryIndexedTree {
public:
    explicit BinaryIndexedTree(unsigned size)
        : nodes_(1 + size)
    {}

    template <typename Iterator>
    BinaryIndexedTree(Iterator begin, Iterator end)
    {
        nodes_.emplace_back();
        nodes_.insert(nodes_.end(), begin, end);

        for (unsigned i = 1; i < nodes_.size(); ++i) {
            if (const unsigned p = i + (i & -i); p < nodes_.size())
                nodes_[p] += nodes_[i];
        }
    }

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

    unsigned search(T target_sum) const
    {
        unsigned p = 0;
        for (unsigned i = 1 << w - __builtin_clz(nodes_.size()); i != 0; i >>= 1) {
            if (p + i < nodes_.size() && nodes_[p + i] < target_sum) {
                p += i;
                target_sum -= nodes_[p];
            }
        }
        return p;
    }

private:
    std::vector<T> nodes_;

    static constexpr unsigned w = __builtin_clz(1);

}; // class BinaryIndexedTree<T>

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    unsigned n;
    std::cin >> n;

    std::vector<unsigned> xs(n);
    for (unsigned i = 0; i < n; ++i)
        std::cin >> xs[i];

    const std::vector<unsigned> ks(n, 1);

    BinaryIndexedTree<unsigned> bit(ks.begin(), ks.end());
    for (unsigned i = 0; i < n; ++i) {
        unsigned p;
        std::cin >> p;

        const unsigned x = bit.search(p);
        std::cout << xs[x] << ' ';
        bit.update(x, -1);
    }

    return 0;
}
