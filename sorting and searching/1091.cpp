#include <iostream>
#include <set>

int main()
{
    unsigned n, m;
    std::cin >> n >> m;

    std::multiset<unsigned> hs;
    for (unsigned i = 0; i < n; ++i) {
        unsigned h;
        std::cin >> h;

        hs.insert(h);
    }

    for (unsigned i = 0; i < m; ++i) {
        unsigned t;
        std::cin >> t;

        auto it = hs.upper_bound(t);
        if (it == hs.begin()) {
            std::cout << -1 << '\n';
        } else {
            std::cout << *--it << '\n';
            hs.erase(it);
        }
    }

    return 0;
}
