#include <iostream>
#include <string>

char determine_digit(unsigned long long k)
{
    unsigned p = 1;
    for (unsigned long long b = 10; p * b < k; b *= 10) {
        k += b;
        ++p;
    }

    return std::to_string(k / p)[k % p];
}

int main()
{
    unsigned q;
    std::cin >> q;

    for (unsigned i = 0; i < q; ++i) {
        unsigned long long k;
        std::cin >> k;

        std::cout << determine_digit(k) << '\n';
    }

    return 0;
}
