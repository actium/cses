#include <iostream>
#include <vector>

struct Point {
    unsigned x;
    unsigned y;
};

struct Line {
    int k;
    int b;

    Line() = default;

    Line(const Point& s, const Point& t)
    {
        const int dx = t.x - s.x, dy = t.y - s.y;
        k = dy / dx;
        b = s.y - dy * s.x;
    }

    unsigned operator ()(unsigned x) const
    {
        return k * x + b;
    }
};

class LineTree {
public:
    explicit LineTree(unsigned size)
        : size_(1 << (w - __builtin_clz(size) + 1))
        , nodes_(2 * size_)
    {}

    void insert(const Point& s, const Point& t)
    {
        insert(1, 0, size_, Line(s, t));
    }

    unsigned query(unsigned x) const
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

    unsigned query(unsigned index, unsigned range_begin, unsigned range_end, unsigned x) const
    {
        unsigned v = nodes_[index](x);
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

    unsigned n, m;
    std::cin >> n >> m;

    LineTree lt(m+1);
    for (unsigned i = 0; i < n; ++i) {
        unsigned y1, y2;
        std::cin >> y1 >> y2;

        lt.insert({0, y1}, {m, y2});
    }

    for (unsigned i = 0; i <= m; ++i)
        std::cout << lt.query(i) << ' ';

    return 0;
}
