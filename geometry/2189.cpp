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

int main()
{
    unsigned t;
    std::cin >> t;

    for (unsigned i = 0; i < t; ++i) {
        Point<long long> p[3];
        std::cin >> p[0] >> p[1] >> p[2];

        const long long cp = cross_product(p[1] - p[0], p[2] - p[0]);
        if (cp > 0)
            std::cout << "LEFT" << '\n';
        if (cp == 0)
            std::cout << "TOUCH" << '\n';
        if (cp < 0)
            std::cout << "RIGHT" << '\n';
    }

    return 0;
}
