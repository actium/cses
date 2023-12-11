#include <algorithm>
#include <iostream>
#include <vector>

int main()
{
    unsigned n;
    std::cin >> n;

    std::vector<unsigned> xs(n);
    for (unsigned i = 0; i < n; ++i)
        std::cin >> xs[i];

    std::sort(xs.begin(), xs.end());

    unsigned long long s = 1;
    for (unsigned i = 0; i < n && xs[i] <= s; ++i)
        s += xs[i];

    std::cout << s;

    return 0;
}
