#include <iostream>
#include <map>
#include <vector>

int main()
{
    unsigned n, k;
    std::cin >> n >> k;

    std::vector<unsigned> xs(n);
    for (unsigned i = 0; i < n; ++i)
        std::cin >> xs[i];

    unsigned long long q = 0;
    std::map<unsigned, unsigned> fs;
    for (unsigned i = 0, j = 0; i < n; ++i) {
        ++fs[xs[i]];

        while (fs.size() > k) {
            const auto it = fs.find(xs[j++]);
            if (--it->second == 0)
                fs.erase(it);
        }

        q += i - j + 1;
    }

    std::cout << q;

    return 0;
}
