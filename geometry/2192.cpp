#include <iostream>
#include <vector>

#include <cmath>

template <typename T>
struct Vector {
    T dx;
    T dy;
};

template <typename T>
constexpr T dot_product(const Vector<T>& lhs, const Vector<T>& rhs) noexcept
{
    return lhs.dx * rhs.dx + lhs.dy * rhs.dy;
}

template <typename T>
constexpr T cross_product(const Vector<T>& lhs, const Vector<T>& rhs) noexcept
{
    return lhs.dx * rhs.dy - lhs.dy * rhs.dx;
}

template <typename T>
double angle(const Vector<T>& u, const Vector<T>& v) noexcept
{
    return std::atan2(cross_product(u, v), dot_product(u, v));
}

template <typename T>
struct Point {
    T x;
    T y;
};

template <typename T>
constexpr Vector<T> operator -(const Point<T>& lhs, const Point<T>& rhs) noexcept
{
    return { lhs.x - rhs.x, lhs.y - rhs.y };
}

template <typename T>
constexpr bool on_segment(const Point<T>& s, const Point<T>& t, const Point<T>& q) noexcept
{
    return q.x >= std::min(s.x, t.x) && q.x <= std::max(s.x, t.x)
        && q.y >= std::min(s.y, t.y) && q.y <= std::max(s.y, t.y);
}

const char* solve(const std::vector<Point<long long>>& ps, const Point<long long>& q)
{
    double a = 0;
    for (auto it = ps.begin(), jt = std::next(it); jt != ps.end(); it = jt++) {
        const Vector<long long> u = *it - q, v = *jt - q;

        if (cross_product(u, v) == 0 && on_segment(*it, *jt, q))
            return "BOUNDARY";

        a += angle(u, v);
    }
    return std::abs(a) > 3.14 ? "INSIDE" : "OUTSIDE";
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    unsigned n, m;
    std::cin >> n >> m;

    std::vector<Point<long long>> ps(n);
    for (unsigned i = 0; i < n; ++i)
        std::cin >> ps[i].x >> ps[i].y;

    ps.push_back(ps[0]);

    for (unsigned i = 0; i < m; ++i) {
        Point<long long> q;
        std::cin >> q.x >> q.y;

        std::cout << solve(ps, q) << '\n';
    }

    return 0;
}
