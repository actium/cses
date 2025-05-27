#include <algorithm>
#include <iostream>
#include <vector>

using integer = unsigned long long;

constexpr integer oo = ~integer(0);

struct Point {
    int x;
    int y;
};

integer distance(const Point& s, const Point& t)
{
    const integer dx = t.x - s.x, dy = t.y - s.y;
    return dx * dx + dy * dy;
}

integer solve(std::vector<Point>& ps, unsigned begin, unsigned end)
{
    integer d = oo;
    if (end - begin < 8) {
        for (unsigned i = begin; i < end; ++i) {
            for (unsigned j = begin; j < i; ++j)
                d = std::min(d, distance(ps[i], ps[j]));
        }
        return d;
    }

    const unsigned mid = (begin + end) / 2;

    d = std::min(d, solve(ps, begin, mid));
    d = std::min(d, solve(ps, mid, end));

    const int x = (ps[mid-1].x + ps[mid].x) / 2;

    std::vector<Point> s;
    for (unsigned i = begin; i < end; ++i) {
        const integer dx = std::abs(x - ps[i].x);
        if (dx * dx < d)
            s.push_back(ps[i]);
    }

    std::sort(s.begin(), s.end(), [](const Point& lhs, const Point& rhs) {
        return lhs.y < rhs.y;
    });

    for (auto it = s.begin(); it != s.end(); ++it) {
        for (auto jt = std::next(it); jt != s.end(); ++jt) {
            const integer dy = jt->y - it->y;
            if (dy * dy >= d)
                break;

            d = std::min(d, distance(*it, *jt));
        }
    }

    return d;
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    unsigned n;
    std::cin >> n;

    std::vector<Point> ps(n);
    for (unsigned i = 0; i < n; ++i)
        std::cin >> ps[i].x >> ps[i].y;

    std::sort(ps.begin(), ps.end(), [](const Point& lhs, const Point& rhs) {
        return lhs.x != rhs.x ? lhs.x < rhs.x : lhs.y > rhs.y;
    });

    std::cout << solve(ps, 0, n) << '\n';

    return 0;
}
