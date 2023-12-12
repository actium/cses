#include <iostream>

using integer = unsigned long long;

constexpr unsigned M = 1000000007;

void multiply(unsigned lhs[4], const unsigned rhs[4])
{
    const unsigned long long product[4] = {
        1ull * lhs[0] * rhs[0] % M + 1ull * lhs[1] * rhs[2] % M,
        1ull * lhs[0] * rhs[1] % M + 1ull * lhs[1] * rhs[3] % M,
        1ull * lhs[2] * rhs[0] % M + 1ull * lhs[3] * rhs[2] % M,
        1ull * lhs[2] * rhs[1] % M + 1ull * lhs[3] * rhs[3] % M,
    };

    for (unsigned i = 0; i < 4; ++i)
        lhs[i] = product[i] % M;
}

unsigned F(integer n)
{
    if (n < 2)
        return n;

    unsigned b[4] = { 0, 1, 1, 1 }, v[4] = { 1, 0, 0, 1 };
    for (integer p = n - 2; p != 0; p /= 2) {
        if (p % 2 == 1)
            multiply(v, b);

        multiply(b, b);
    }

    return (v[2] + v[3]) % M;
}

int main()
{
    integer n;
    std::cin >> n;

    std::cout << F(n);

    return 0;
}
