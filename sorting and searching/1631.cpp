#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

int main()
{
    unsigned n;
    std::cin >> n;

    std::vector<unsigned> ts(n);
    for (unsigned i = 0; i < n; ++i)
        std::cin >> ts[i];

    const unsigned long long s = std::accumulate(ts.begin(), ts.end(), 0ull);
    const unsigned x = *std::max_element(ts.begin(), ts.end());

    std::cout << std::max(s, 2ull * x);

    return 0;
}
