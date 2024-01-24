#include <iostream>
#include <vector>

template <typename T>
class BinaryIndexedTree {
public:
    explicit BinaryIndexedTree(unsigned size)
        : nodes_(1 + size, std::vector<T>(1 + size))
    {}

    template <typename U>
    void update(unsigned x, unsigned y, U delta)
    {
        for (unsigned i = x + 1; i < nodes_.size(); i += i & -i) {
            for (unsigned j = y + 1; j < nodes_.size(); j += j & -j)
                nodes_[i][j] += delta;
        }
    }

    T sum(unsigned x, unsigned y) const
    {
        auto sum = T();
        for (unsigned i = x + 1; i > 0; i &= i - 1) {
            for (unsigned j = y + 1; j > 0; j &= j - 1)
                sum += nodes_[i][j];
        }
        return sum;
    }

    T sum(unsigned x1, unsigned y1, unsigned x2, unsigned y2) const
    {
        return sum(x2, y2) - sum(x1 - 1, y2) - sum(x2, y1 - 1) + sum(x1 - 1, y1 - 1);
    }

private:
    std::vector<std::vector<T>> nodes_;

    static constexpr unsigned w = __builtin_clz(1);

}; // class BinaryIndexedTree<T>

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    unsigned n, q;
    std::cin >> n >> q;

    std::vector<std::string> grid(n);
    for (unsigned i = 0; i < n; ++i)
        std::cin >> grid[i];

    BinaryIndexedTree<unsigned> bit(n);
    for (unsigned i = 0; i < n; ++i) {
        for (unsigned j = 0; j < n; ++j) {
            if (grid[i][j] == '*')
                bit.update(i, j, 1);
        }
    }

    for (unsigned i = 0; i < q; ++i) {
        unsigned t;
        std::cin >> t;

        if (t == 1) {
            unsigned x, y;
            std::cin >> x >> y;

            if (grid[x-1][y-1] == '*') {
                grid[x-1][y-1] = '.';
                bit.update(x-1, y-1, -1);
            } else {
                grid[x-1][y-1] = '*';
                bit.update(x-1, y-1, 1);
            }
        } else {
            unsigned x1, y1, x2, y2;
            std::cin >> x1 >> y1 >> x2 >> y2;

            std::cout << bit.sum(x1-1, y1-1, x2-1, y2-1) << '\n';
        }
    }

    return 0;
}
