#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

struct Point {
    int x;
    int y;
};

std::istream& operator >>(std::istream& input, Point& p)
{
    return input >> p.x >> p.y;
}

bool operator <(const Point& lhs, const Point& rhs)
{
    return lhs.x != rhs.x ? lhs.x < rhs.x : lhs.y < rhs.y;
}

int relative_location(const Point& p, const Point& q, const Point& r) noexcept
{
    const long long u = 1LL * p.x * q.y + 1LL * q.x * r.y + 1LL * r.x * p.y;
    const long long v = 1LL * p.y * q.x + 1LL * q.y * r.x + 1LL * r.y * p.x;
    return u < v ? -1 : u > v;
}

template <typename F>
std::vector<Point> convex_hull(std::vector<Point> ps, F&& order)
{
    const unsigned n = ps.size();

    std::sort(ps.begin() + 1, ps.end(), [&](const Point& lhs, const Point& rhs) {
        const int s = relative_location(ps[0], lhs, rhs);
        if (s != 0)
            return s > 0;

        const long long ldx = lhs.x - ps[0].x, ldy = lhs.y - ps[0].y;
        const long long rdx = rhs.x - ps[0].x, rdy = rhs.y - ps[0].y;
        return order(ldx * ldx + ldy * ldy, rdx * rdx + rdy * rdy);
    });

    unsigned k = 0;
    for (unsigned i = 0; i < n; ++i) {
        while (k > 2 && relative_location(ps[k-2], ps[k-1], ps[i]) < 0)
            --k;

        ps[k++] = ps[i];
    }

    ps.resize(k);
    return ps;
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    unsigned n;
    std::cin >> n;

    std::vector<Point> ps(n);
    for (unsigned i = 0; i < n; ++i)
        std::cin >> ps[i];

    std::swap(ps[0], *std::min_element(ps.begin(), ps.end()));

    const std::vector<Point> ch1 = convex_hull(ps, [](long long d1, long long d2) { return d1 < d2; });
    const std::vector<Point> ch2 = convex_hull(ps, [](long long d1, long long d2) { return d1 > d2; });

    std::set<Point> ch;
    ch.insert(ch1.begin(), ch1.end());
    ch.insert(ch2.begin(), ch2.end());

    std::cout << ch.size() << '\n';
    for (const Point& p : ch)
        std::cout << p.x << ' ' << p.y << '\n';

    return 0;
}
