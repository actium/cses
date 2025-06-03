#include <iostream>
#include <set>
#include <vector>

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    unsigned n, k;
    std::cin >> n >> k;

    std::vector<unsigned> xs(n);
    for (unsigned i = 0; i < n; ++i)
        std::cin >> xs[i];

    std::set<unsigned> s;
    for (unsigned i = 0; i <= k; ++i)
        s.insert(i);

    std::vector<unsigned> f(1+k);
    for (unsigned i = 0; i < k; ++i) {
        if (xs[i] <= k && ++f[xs[i]] == 1)
            s.erase(xs[i]);
    }

    std::cout << *s.begin();

    for (unsigned i = k; i < n; ++i) {
        if (xs[i] <= k && ++f[xs[i]] == 1)
            s.erase(xs[i]);

        if (xs[i-k] <= k && --f[xs[i-k]] == 0)
            s.insert(xs[i-k]);

        std::cout << ' ' << *s.begin();
    }

    return 0;
}
