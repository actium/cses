#include <algorithm>
#include <iostream>
#include <vector>

using integer = unsigned long long;

constexpr unsigned M = 1000000007;

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

    unsigned n;
    std::cin >> n;

    std::vector<unsigned> xs(n);
    for (unsigned i = 0; i < n; ++i)
        std::cin >> xs[i];

    compress(xs);

    BinaryIndexedTree<integer> bit(1+n);
    for (const unsigned x : xs)
        bit.update(x, bit.sum(0, x) % M + 1);

    std::cout << bit.sum(0, n+1) % M << '\n';

    return 0;
}
