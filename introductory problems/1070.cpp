#include <iostream>

int main()
{
    unsigned n;
    std::cin >> n;

    if (n == 2 || n == 3) {
        std::cout << "NO SOLUTION";
    } else {
        for (unsigned i = 2; i <= n; i += 2)
            std::cout << i << ' ';

        for (unsigned i = 1; i <= n; i += 2)
            std::cout << i << ' ';
    }

    return 0;
}
