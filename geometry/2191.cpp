#include <iostream>
#include <vector>

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

    long long a = 0;
    for (unsigned i = 1; i <= n; ++i)
        a += 1LL * ps[i-1].x * ps[i].y - 1LL * ps[i].x * ps[i-1].y;

    std::cout << std::abs(a) << '\n';

    return 0;
}
