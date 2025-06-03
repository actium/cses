#include <iostream>
#include <vector>

using integer = unsigned long long;

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    unsigned n, k;
    std::cin >> n >> k;

    unsigned x, a, b, c;
    std::cin >> x >> a >> b >> c;

    std::vector<integer> v(n);
    {
        v[0] = x;
        for (unsigned i = 1; i < n; ++i)
            v[i] = (a * v[i-1] + b) % c;
    }

    integer s = 0;
    for (unsigned i = 0; i < k; ++i)
        s += v[i];

    integer sum = s;
    for (unsigned i = k; i < n; ++i) {
        s += v[i] - v[i-k];
        sum ^= s;
    }

    std::cout << sum << '\n';

    return 0;
}
