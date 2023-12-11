#include <algorithm>
#include <iostream>
#include <vector>

int main()
{
    unsigned n;
    std::cin >> n;

    std::vector<unsigned> cs;
    for (unsigned i = 0; i < n; ++i) {
        unsigned k;
        std::cin >> k;

        const auto it = std::upper_bound(cs.begin(), cs.end(), k);
        if (it == cs.end())
            cs.push_back(k);
        else
            *it = k;
    }

    std::cout << cs.size();

    return 0;
}
