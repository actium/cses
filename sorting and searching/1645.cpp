#include <iostream>
#include <vector>

int main()
{
    unsigned n;
    std::cin >> n;

    std::vector<unsigned> xs(1 + n);
    for (unsigned i = 1; i <= n; ++i)
        std::cin >> xs[i];

    std::vector<unsigned> ps(1 + n);
    for (unsigned i = 2; i <= n; ++i) {
        unsigned j = i - 1;
        while (xs[i] <= xs[j])
            j = ps[j];

        ps[i] = j;
    }

    for (unsigned i = 1; i <= n; ++i)
        std::cout << ps[i] << ' ';

    return 0;
}
