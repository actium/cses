#include <iostream>
#include <map>
#include <vector>

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    unsigned n, k;
    std::cin >> n >> k;

    std::vector<unsigned> xs(n);
    for (unsigned i = 0; i < n; ++i)
        std::cin >> xs[i];

    std::map<unsigned, unsigned> f;
    for (unsigned i = 0; i < k; ++i)
        ++f[xs[i]];

    std::cout << f.size();

    for (unsigned i = k; i < n; ++i) {
        ++f[xs[i]];

        if (--f[xs[i-k]] == 0)
            f.erase(xs[i-k]);

        std::cout << ' ' << f.size();
    }

    return 0;
}
