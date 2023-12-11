#include <algorithm>
#include <iostream>
#include <vector>

int main()
{
    unsigned n;
    std::cin >> n;

    std::vector<unsigned> p(n);
    for (unsigned i = 0; i < n; ++i)
        std::cin >> p[i];

    std::sort(p.begin(), p.end());

    const unsigned m = p[n/2];

    unsigned long long s = 0;
    for (const unsigned x : p)
        s += abs(x - m);

    std::cout << s;

    return 0;
}
