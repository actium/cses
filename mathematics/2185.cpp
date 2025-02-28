#include <iostream>
#include <vector>

using integer = unsigned long long;

integer count(integer n, const std::vector<integer>& a)
{
    const unsigned k = a.size(), m = 1 << k;

    integer q[2] = {};
    for (unsigned i = 1; i < m; ++i) {
        __int128_t p = 1;
        for (unsigned x = i; x != 0 && p <= n; x &= x-1)
            p *= a[__builtin_ctz(x)];

        q[__builtin_popcount(i) % 2] += n / p;
    }

    return q[1] - q[0];
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    integer n;
    std::cin >> n;

    unsigned k;
    std::cin >> k;

    std::vector<integer> a(k);
    for (unsigned i = 0; i < k; ++i)
        std::cin >> a[i];

    std::cout << count(n, a) << '\n';

    return 0;
}
