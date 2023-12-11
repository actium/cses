#include <iostream>
#include <map>
#include <set>

int main()
{
    unsigned x, n;
    std::cin >> x >> n;

    std::set<unsigned> ps = { 0, x };
    std::map<unsigned, unsigned> fs = { { x, 1 } };
    for (unsigned i = 0; i < n; ++i) {
        unsigned p;
        std::cin >> p;

        const auto it = ps.lower_bound(p);
        {
            const unsigned lb = *std::prev(it), ub = *it;
            if (--fs[ub - lb] == 0)
                fs.erase(ub - lb);

            ++fs[p - lb];
            ++fs[ub - p];
        }
        ps.insert(p);

        std::cout << fs.rbegin()->first << ' ';
    }

    return 0;
}
