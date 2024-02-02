#include <algorithm>
#include <iostream>
#include <vector>

struct Range {
    unsigned i;
    unsigned x;
    unsigned y;
};

std::ostream& operator <<(std::ostream& output, const std::vector<unsigned>& v)
{
    for (const unsigned x : v)
        output << x << ' ';

    return output;
}

void solve(std::vector<Range>& rs)
{
    const unsigned n = rs.size();

    std::sort(rs.begin(), rs.end(), [](const Range& lhs, const Range& rhs) {
        return lhs.x != rhs.x ? lhs.x < rhs.x : lhs.y > rhs.y;
    });

    std::vector<unsigned> a(n), b(n);
    for (unsigned i = 0, lb = ~0u, ub = 0; i < n; ++i) {
        if (rs[n-1-i].y >= lb)
            a[rs[n-1-i].i] = 1;
        else
            lb = rs[n-1-i].y;

        if (rs[i].y <= ub)
            b[rs[i].i] = 1;
        else
            ub = rs[i].y;
    }

    std::cout << a << '\n';
    std::cout << b << '\n';
}

int main()
{
    unsigned n;
    std::cin >> n;

    std::vector<Range> rs(n);
    for (unsigned i = 0; i < n; ++i) {
        std::cin >> rs[i].x >> rs[i].y;

        rs[i].i = i;
    }

    solve(rs);

    return 0;
}
