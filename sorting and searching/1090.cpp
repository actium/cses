#include <algorithm>
#include <iostream>
#include <vector>

int main()
{
    unsigned n, x;
    std::cin >> n >> x;

    std::vector<unsigned> p(n);
    for (unsigned i = 0; i < n; ++i)
        std::cin >> p[i];

    std::sort(p.begin(), p.end());

    unsigned k = 0;
    for (unsigned i = 0, j = n; i < j; --j) {
        if (p[i] + p[j-1] <= x)
            ++i;

        ++k;
    }

    std::cout << k;

    return 0;
}
