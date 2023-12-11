#include <iostream>

int main()
{
    unsigned long long n;
    std::cin >> n;

    unsigned long long s = n * (n + 1) / 2;
    while (--n > 0) {
        unsigned x;
        std::cin >> x;

        s -= x;
    }

    std::cout << s;

    return 0;
}
