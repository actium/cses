#include <iostream>

constexpr unsigned M = 1000000007;

unsigned a(unsigned n)
{
    if (n == 0)
        return 1;

    return (1ull * n * a(n-1) + (n % 2 == 0 ? 1 : -1)) % M;
}

int main()
{
    unsigned n;
    std::cin >> n;

    std::cout << a(n);

    return 0;
}
