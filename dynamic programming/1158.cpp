#include <iostream>
#include <vector>

int main()
{
    unsigned n, x;
    std::cin >> n >> x;

    std::vector<unsigned> hs(n);
    for (unsigned i = 0; i < n; ++i)
        std::cin >> hs[i];

    std::vector<unsigned> ss(n);
    for (unsigned i = 0; i < n; ++i)
        std::cin >> ss[i];

    std::vector<unsigned> counts(1 + x);
    for (unsigned i = 0; i < n; ++i) {
        for (unsigned j = x; j >= hs[i]; --j)
            counts[j] = std::max(counts[j], counts[j- hs[i]] + ss[i]);
    }

    std::cout << counts[x];

    return 0;
}
