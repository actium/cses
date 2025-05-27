#include <iostream>
#include <vector>

#include <climits>

struct Line {
    int k = 0;
    long long b = LONG_LONG_MIN;

    Line() = default;

    Line(int k, int b)
        : k(k)
        , b(b)
    {}

    long long operator ()(unsigned x) const
    {
        return 1LL * k * x + b;
    }
};

class LineTree {
public:
    explicit LineTree(unsigned size)
        : size_(1 << (w - __builtin_clz(size) + 1))
        , nodes_(2 * size_)
    {}

    void insert(const Line& line)
    {
        insert(1, 0, size_, line);
    }

    long long query(unsigned x) const
    {
        return query(1, 0, size_, x);
    }

private:
    void insert(unsigned index, unsigned range_begin, unsigned range_end, Line line)
    {
        const unsigned mid = (range_begin + range_end) / 2;

        const bool p = (line(range_begin) > nodes_[index](range_begin));
        const bool q = (line(mid) > nodes_[index](mid));

        if (q)
            std::swap(line, nodes_[index]);

        if (range_end - range_begin == 1)
            return;

        if (p != q)
            insert(index<<1|0, range_begin, mid, line);
        else
            insert(index<<1|1, mid, range_end, line);
    }

    long long query(unsigned index, unsigned range_begin, unsigned range_end, unsigned x) const
    {
        long long v = nodes_[index](x);
        if (range_end - range_begin > 1) {
            const unsigned mid = (range_begin + range_end) / 2;
            v = std::max(v, x < mid ? query(index<<1|0, range_begin, mid, x) : query(index<<1|1, mid, range_end, x));
        }
        return v;
    }

private:
    const unsigned size_;

    std::vector<Line> nodes_;

    static constexpr unsigned w = __builtin_clz(1);

}; // class LineTree

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    unsigned n;
    std::cin >> n;

    LineTree lt(100001);
    for (unsigned i = 0; i < n; ++i) {
        unsigned t;
        std::cin >> t;

        if (t == 1) {
            int a, b;
            std::cin >> a >> b;

            lt.insert(Line(a, b));
        } else {
            unsigned x;
            std::cin >> x;

            std::cout << lt.query(x) << '\n';
        }
    }

    return 0;
}
