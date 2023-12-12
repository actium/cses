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

    unsigned s = 0;
    for (const unsigned x : xs)
        s += x;

    std::vector<bool> dp(1 + s);
    dp[0] = true;
    for (const unsigned x : xs) {
        for (unsigned i = s; i >= x; --i)
            dp[i] = dp[i] || dp[i-x];
    }

    std::cout << std::count(dp.begin() + 1, dp.end(), true) << '\n';
    for (unsigned i = 1; i <= s; ++i) {
        if (dp[i])
            std::cout << i << ' ';
    }

    return 0;
}
