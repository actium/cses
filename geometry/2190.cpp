#include <iostream>

template <typename T>
struct Vector {
    T dx;
    T dy;
};

template <typename T>
constexpr T cross_product(const Vector<T>& lhs, const Vector<T>& rhs) noexcept
{
    return lhs.dx * rhs.dy - lhs.dy * rhs.dx;
}

template <typename T>
struct Point {
    T x;
    T y;

    constexpr Point() noexcept
        : Point(0, 0)
    {}

    constexpr Point(T x, T y) noexcept
        : x(x)
        , y(y)
    {}
};

template <typename T>
std::istream& operator >>(std::istream& input, Point<T>& point)
{
    return input >> point.x >> point.y;
}

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

int main()
{
    unsigned t;
    std::cin >> t;

    for (unsigned i = 0; i < t; ++i) {
        Point<long long> p[4];
        std::cin >> p[0] >> p[1] >> p[2] >> p[3];

        const long long cp1 = cross_product(p[1] - p[0], p[2] - p[0]), cp2 = cross_product(p[1] - p[0], p[3] - p[0]);
        if (cp1 != 0 && cp2 != 0 && (cp1 < 0) == (cp2 < 0)) {
            std::cout << "NO" << '\n';
            continue;
        }

        const long long cp3 = cross_product(p[3] - p[2], p[0] - p[2]), cp4 = cross_product(p[3] - p[2], p[1] - p[2]);
        if (cp3 != 0 && cp4 != 0 && (cp3 < 0) == (cp4 < 0)) {
            std::cout << "NO" << '\n';
            continue;
        }

        if (cp1 != 0 || cp2 != 0 || cp3 != 0 || cp4 != 0) {
            std::cout << "YES" << '\n';
            continue;
        }

        if (on_segment(p[0], p[1], p[2]) || on_segment(p[0], p[1], p[3]) || on_segment(p[2], p[3], p[0]) || on_segment(p[2], p[3], p[1])) {
            std::cout << "YES" << '\n';
            continue;
        }

        std::cout << "NO" << '\n';
    }

    return 0;
}
