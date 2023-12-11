#include <algorithm>
#include <iostream>
#include <map>
#include <vector>

struct Customer {
    unsigned a;
    unsigned b;
    unsigned i;
};

int main()
{
    unsigned n;
    std::cin >> n;

    std::vector<Customer> cs(n);
    for (unsigned i = 0; i < n; ++i) {
        std::cin >> cs[i].a >> cs[i].b;

        cs[i].i = i;
    }

    std::sort(cs.begin(), cs.end(), [](const Customer& u, const Customer& v) {
        return u.a > v.a;
    });

    unsigned k = 0;

    std::vector<unsigned> ps(n);
    std::multimap<unsigned, unsigned> rs;
    for (const Customer& c : cs) {
        const auto it = rs.lower_bound(c.b + 1);
        if (it == rs.end()) {
            ps[c.i] = ++k;
        } else {
            ps[c.i] = it->second;
            rs.erase(it);
        }
        rs.emplace(c.a, ps[c.i]);
    }

    std::cout << k << '\n';
    for (unsigned i = 0; i < n; ++i)
        std::cout << ps[i] << ' ';

    return 0;
}
