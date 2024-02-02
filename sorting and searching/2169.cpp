#include <algorithm>
#include <iostream>
#include <vector>

struct Range {
    unsigned i;
    unsigned x;
    unsigned y;
};

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

    static constexpr unsigned w = __builtin_clz(1);

}; // class BinaryIndexedTree<T>

std::ostream& operator <<(std::ostream& output, const std::vector<unsigned>& v)
{
    for (const unsigned x : v)
        output << x << ' ';

    return output;
}

void solve(std::vector<Range>& rs)
{
    const unsigned n = rs.size();

    std::sort(rs.begin(), rs.end(), [](const Range& lhs, const Range& rhs) {
        return lhs.x != rhs.x ? lhs.x < rhs.x : lhs.y > rhs.y;
    });

    {
        std::vector<unsigned> c(n);
        for (unsigned i = 0; i < n; ++i)
            c[i] = rs[i].y;

        std::sort(c.begin(), c.end());

        for (Range& r : rs)
            r.y = std::lower_bound(c.begin(), c.end(), r.y) - c.begin();
    }

    std::vector<unsigned> a(n);
    {
        BinaryIndexedTree<unsigned> bit(n);
        for (auto it = rs.rbegin(); it != rs.rend(); ++it) {
            a[it->i] = bit.sum(0, it->y + 1);
            bit.update(it->y, 1);
        }
    }
    std::cout << a << '\n';

    std::vector<unsigned> b(n);
    {
        BinaryIndexedTree<unsigned> bit(n);
        for (auto it = rs.begin(); it != rs.end(); ++it) {
            b[it->i] = bit.sum(it->y, n);
            bit.update(it->y, 1);
        }
    }
    std::cout << b << '\n';
}

int main()
{
    unsigned n;
    std::cin >> n;

    std::vector<Range> rs(n);
    for (unsigned i = 0; i < n; ++i) {
        std::cin >> rs[i].x >> rs[i].y;

        rs[i].i = i;
    }

    solve(rs);

    return 0;
}
