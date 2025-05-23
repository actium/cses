#include <iostream>

using integer = long long;

constexpr integer oo = 1LL << 60;

integer distance(const std::pair<integer, integer>& lhs, const std::pair<integer, integer>& rhs)
{
    return std::max(std::abs(lhs.first - rhs.first), std::abs(lhs.second - rhs.second));
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    unsigned n;
    std::cin >> n;

    std::pair<integer, integer> st[2] = { { oo, oo }, { -oo, -oo } }, ts[2] = { { oo, oo }, { -oo, -oo } };
    for (unsigned i = 0; i < n; ++i) {
        int x, y;
        std::cin >> x >> y;

        const integer s = x + y, t = x - y;

        st[0] = std::min(st[0], std::make_pair(s, t));
        st[1] = std::max(st[1], std::make_pair(s, t));
        ts[0] = std::min(ts[0], std::make_pair(t, s));
        ts[1] = std::max(ts[1], std::make_pair(t, s));

        std::cout << std::max(distance(st[0], st[1]), distance(ts[0], ts[1])) << '\n';
    }

    return 0;
}
