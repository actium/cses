#include <iostream>

constexpr unsigned M = 1000000007;

int main()
{
    unsigned n;
    std::cin >> n;

    unsigned long long k = 1;
    for (unsigned long long b = 2; n != 0; n /= 2) {
        if (n % 2 == 1)
            k = k * b % M;

        b = b * b % M;
    }

    std::cout << k;

    return 0;
}
