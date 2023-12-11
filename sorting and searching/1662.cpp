#include <iostream>
#include <map>
#include <vector>

int main()
{
    unsigned n;
    std::cin >> n;

    std::vector<int> as(n);
    for (unsigned i = 0; i < n; ++i)
        std::cin >> as[i];

    long long s = 0, k = 0;
    std::map<unsigned, unsigned> f = { { 0, 1 } };
    for (const int a : as) {
        s = ((s + a) % n + n) % n;
        k += f[s]++;
    }

    std::cout << k;

    return 0;
}
