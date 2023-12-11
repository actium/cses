#include <iostream>
#include <map>
#include <vector>

int main()
{
    unsigned n;
    std::cin >> n;

    int x;
    std::cin >> x;

    std::vector<int> as(n);
    for (unsigned i = 0; i < n; ++i)
        std::cin >> as[i];

    long long s = 0, k = 0;
    std::map<long long, unsigned> fs = { { 0, 1 } };
    for (const int a : as) {
        s += a;
        k += fs[s - x];
        ++fs[s];
    }

    std::cout << k;

    return 0;
}
