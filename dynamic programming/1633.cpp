#include <iostream>
#include <vector>

constexpr unsigned M = 1000000007;

int main()
{
    unsigned n;
    std::cin >> n;

    std::vector<unsigned> cs(1+n);
    cs[0] = 1;
    for (unsigned i = 1; i <= n; ++i) {
        for (unsigned d = 1; d <= 6 && d <= i; ++d)
            cs[i] = (cs[i] + cs[i-d]) % M;
    }

    std::cout << cs[n];

    return 0;
}
