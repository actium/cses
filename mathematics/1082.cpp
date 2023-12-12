#include <iostream>

using integer = unsigned long long;

constexpr unsigned M = 1000000007;

int main()
{
    integer n;
    std::cin >> n;

    const auto c = [](integer x) {
        return x % M * ((x - 1) % M) % M * (M + 1) / 2 % M;
    };

    integer s = 0;
    for (integer i = 1; i <= n; ++i) {
        const integer k = n / i, q = n / k;
        s = (s + k % M * (c(q + 1) - c(i) + M)) % M;
        i = q;
    }

    std::cout << s;

    return 0;
}
