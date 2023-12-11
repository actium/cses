#include <algorithm>
#include <iostream>
#include <vector>

int main()
{
    unsigned n;
    std::cin >> n;

    std::vector<unsigned> x(n);
    for (unsigned i = 0; i < n; ++i)
        std::cin >> x[i];

    std::sort(x.begin(), x.end());

    std::cout << std::unique(x.begin(), x.end()) - x.begin();

    return 0;
}
