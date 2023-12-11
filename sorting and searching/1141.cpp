#include <iostream>
#include <set>
#include <vector>

int main()
{
    unsigned n;
    std::cin >> n;

    std::vector<unsigned> ks(n);
    for (unsigned i = 0; i < n; ++i)
        std::cin >> ks[i];

    unsigned q = 0;

    std::set<unsigned> s;
    for (unsigned i = 0, j = 0; i < n; ++i) {
        if (!s.insert(ks[i]).second) {
            while (ks[j] != ks[i])
                s.erase(ks[j++]);

            ++j;
        }

        q = std::max(q, i - j + 1);
    }

    std::cout << q;

    return 0;
}
