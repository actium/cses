#include <iostream>
#include <vector>

int main()
{
    unsigned n, q;
    std::cin >> n >> q;

    std::vector<unsigned> xs(n);
    for (unsigned i = 0; i < n; ++i)
        std::cin >> xs[i];

    std::vector<unsigned long long> ps(1 + n);
    for (unsigned i = 0; i < n; ++i)
        ps[i+1] = ps[i] + xs[i];

    for (unsigned i = 0; i < q; ++i) {
        unsigned a, b;
        std::cin >> a >> b;

        std::cout << ps[b] - ps[a-1] << '\n';
    }

    return 0;
}
