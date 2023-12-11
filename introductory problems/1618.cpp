#include <iostream>

int main()
{
    unsigned n;
    std::cin >> n;

    unsigned k = 0;
    while (n != 0) {
        n /= 5;
        k += n;
    }

    std::cout << k;

    return 0;
}
