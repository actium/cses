#include <iostream>
#include <vector>

unsigned lsb(unsigned x)
{
    return x & -x;
}

template <typename T>
class BinaryIndexedTree {
public:
    template <typename Iterator>
    BinaryIndexedTree(Iterator begin, Iterator end)
    {
        const unsigned size = 1 + std::distance(begin, end);
        data_.reserve(size);
        data_.emplace_back();
        data_.insert(data_.end(), begin, end);

        for (unsigned i = 1; i < size; ++i) {
            const unsigned j = i + lsb(i);
            if (j < size)
                data_[j] += data_[i];
        }
    }

    void adjust(unsigned index, std::make_signed_t<T> delta)
    {
        const unsigned size = data_.size();
        for (unsigned i = 1 + index; i < size; i += lsb(i))
            data_[i] += delta;
    }

    T prefix_sum(unsigned end) const
    {
        T sum = 0;
        for (unsigned i = end; i > 0; i &= i - 1)
            sum += data_[i];

        return sum;
    }

private:
    std::vector<T> data_;

}; // class BinaryIndexedTree<T>

int main()
{
    unsigned n, q;
    std::cin >> n >> q;

    std::vector<unsigned> xs(n);
    for (unsigned i = 0; i < n; ++i)
        std::cin >> xs[i];

    BinaryIndexedTree<unsigned long long> bit(xs.begin(), xs.end());
    for (unsigned i = 0; i < q; ++i) {
        unsigned t;
        std::cin >> t;

        if (t == 1) {
            unsigned k, u;
            std::cin >> k >> u;

            bit.adjust(k-1, u - (bit.prefix_sum(k) - bit.prefix_sum(k-1)));
        } else {
            unsigned a, b;
            std::cin >> a >> b;

            std::cout << bit.prefix_sum(b) - bit.prefix_sum(a-1) << '\n';
        }
    }

    return 0;
}
