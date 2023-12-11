#include <iostream>
#include <vector>

int main()
{
    unsigned n;
    std::cin >> n;

    std::vector<unsigned> xs(n);
    for (unsigned i = 0; i < n; ++i)
        std::cin >> xs[i];

    std::vector<unsigned> p(n);
    for (unsigned i = 0; i < n; ++i)
        p[xs[i]-1] = i;

    unsigned k = 1;
    for (unsigned i = 1; i < n; ++i)
        k += (p[i] < p[i-1]);

    std::cout << k;

    return 0;
}