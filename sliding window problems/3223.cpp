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

void compress(std::vector<unsigned>& xs)
{
    std::vector<unsigned> s = xs;
    std::sort(s.begin(), s.end());
    s.erase(std::unique(s.begin(), s.end()), s.end());

    for (unsigned& x : xs)
        x = std::lower_bound(s.begin(), s.end(), x) - s.begin();
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    unsigned n, k;
    std::cin >> n >> k;

    std::vector<unsigned> xs(n);
    for (unsigned i = 0; i < n; ++i)
        std::cin >> xs[i];

    compress(xs);

    unsigned c = 0;

    BinaryIndexedTree<unsigned> bit(n);
    for (unsigned i = 0; i < k; ++i) {
        c += bit.sum(xs[i] + 1, n);
        bit.update(xs[i], 1);
    }

    std::cout << c;

    for (unsigned i = k; i < n; ++i) {
        c -= bit.sum(0, xs[i-k]);
        bit.update(xs[i-k], -1);

        c += bit.sum(xs[i] + 1, n);
        bit.update(xs[i], 1);

        std::cout << ' ' << c;
    }

    return 0;
}
