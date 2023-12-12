#include <iostream>

struct Point {
    int x;
    int y;
};

std::istream& operator >>(std::istream& input, Point& p)
{
    return input >> p.x >> p.y;
}

struct Vector {
    int dx;
    int dy;
};

Vector operator -(const Point& lhs, const Point& rhs)
{
    return { lhs.x - rhs.x, lhs.y - rhs.y };
}

long long cross_product(const Vector& v1, const Vector& v2)
{
    return 1ll * v1.dy * v2.dx - 1ll * v2.dy * v1.dx;
}

int main()
{
    unsigned t;
    std::cin >> t;

    for (unsigned i = 0; i < t; ++i) {
        Point p[3];
        std::cin >> p[0] >> p[1] >> p[2];

        const long long cp = cross_product(p[1] - p[0], p[2] - p[0]);
        if (cp < 0)
            std::cout << "LEFT" << '\n';
        if (cp == 0)
            std::cout << "TOUCH" << '\n';
        if (cp > 0)
            std::cout << "RIGHT" << '\n';
    }

    return 0;
}
