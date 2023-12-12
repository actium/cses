#include <algorithm>
#include <iostream>
#include <vector>

int main()
{
    unsigned n;
    std::cin >> n;

    std::vector<unsigned> xs(n);
    for (unsigned i = 0; i < n; ++i)
        std::cin >> xs[i];

    std::vector<unsigned> ts;
    for (const unsigned x : xs) {
        const auto it = std::lower_bound(ts.begin(), ts.end(), x);
        if (it != ts.end()) {
            *it = x;
        } else {
            ts.push_back(x);
        }
    }

    std::cout << ts.size();

    return 0;
}
