#include <iostream>
#include <numeric>
#include <vector>

using integer = long long;

struct Point {
    int x;
    int y;
};

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    unsigned n;
    std::cin >> n;

    std::vector<Point> ps(n);
    for (unsigned i = 0; i < n; ++i)
        std::cin >> ps[i].x >> ps[i].y;

    ps.push_back(ps[0]);

    integer s = 0, g = 0;
    for (unsigned i = 1; i <= n; ++i) {
        s += 1LL * ps[i-1].x * ps[i].y - 1LL * ps[i].x * ps[i-1].y;
        g += std::gcd(ps[i].x - ps[i-1].x, ps[i].y - ps[i-1].y);
    }

    std::cout << (std::abs(s) - g) / 2 + 1 << ' ' << g << '\n';

    return 0;
}
