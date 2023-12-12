#include <algorithm>
#include <iostream>
#include <map>
#include <vector>

struct Project {
    unsigned a;
    unsigned b;
    unsigned p;
};

int main()
{
    unsigned n;
    std::cin >> n;

    std::vector<Project> ps(n);
    for (unsigned i = 0; i < n; ++i)
        std::cin >> ps[i].a >> ps[i].b >> ps[i].p;

    std::sort(ps.begin(), ps.end(), [](const Project& u, const Project& v) {
        return u.b < v.b;
    });

    std::map<unsigned, unsigned long long> amounts;
    amounts[0] = 0;

    unsigned long long x = 0;
    for (const Project& p : ps) {
        const auto it = std::prev(amounts.lower_bound(p.a));
        x = std::max(x, it->second + p.p);
        amounts[p.b] = x;
    }

    std::cout << x;

    return 0;
}
