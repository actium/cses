#include <iostream>
#include <vector>

unsigned lsb(unsigned x)
{
    return x & -x;
}

class BinaryIndexedTree {
public:
    explicit BinaryIndexedTree(unsigned size)
        : size_(size)
        , data_(1 + size, std::vector<unsigned>(1 + size))
    {}

    void update(unsigned x, unsigned y, int delta)
    {
        for (unsigned i = 1 + x; i <= size_; i += lsb(i)) {
            for (unsigned j = 1 + y; j <= size_; j += lsb(j))
                data_[i][j] += delta;
        }
    }

    unsigned count(unsigned x, unsigned y) const
    {
        unsigned k = 0;
        for (unsigned i = 1 + x; i > 0; i &= ~lsb(i)) {
            for (unsigned j = 1 + y; j > 0; j &= ~lsb(j))
                k += data_[i][j];
        }
        return k;
    }

    unsigned count(unsigned x1, unsigned y1, unsigned x2, unsigned y2) const
    {
        unsigned k = 0;
        k += count(x2, y2);
        k -= count(x1 - 1, y2);
        k -= count(x2, y1 - 1);
        k += count(x1 - 1, y1 - 1);
        return k;
    }

private:
    const unsigned size_;

    std::vector<std::vector<unsigned>> data_;

}; // class BinaryIndexedTree

int main()
{
    unsigned n, q;
    std::cin >> n >> q;

    BinaryIndexedTree bit(n);
    for (unsigned i = 0; i < n; ++i) {
        std::string s;
        std::cin >> s;

        for (unsigned j = 0; j < n; ++j) {
            if (s[j] == '*')
                bit.update(i, j, 1);
        }
    }

    for (unsigned i = 0; i < q; ++i) {
        unsigned x1, y1, x2, y2;
        std::cin >> x1 >> y1 >> x2 >> y2;

        std::cout << bit.count(x1-1, y1-1, x2-1, y2-1) << '\n';
    }

    return 0;
}
