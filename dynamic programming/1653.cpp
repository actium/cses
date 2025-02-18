#include <iostream>
#include <vector>

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    unsigned n, x;
    std::cin >> n >> x;

    std::vector<unsigned> ws(n);
    for (unsigned i = 0; i < n; ++i)
        std::cin >> ws[i];

    const unsigned m = 1 << n;

    std::vector<std::pair<unsigned, unsigned>> dp(m, { n, ~0u >> 1 });
    dp[0] = { 0, 0 };
    for (unsigned i = 1; i < m; ++i) {
        for (unsigned j = i; j != 0; j &= j-1) {
            const unsigned d = __builtin_ctz(j), k = 1 << d;

            if (dp[i^k].second + ws[d] <= x)
                dp[i] = std::min(dp[i], std::make_pair(dp[i^k].first, dp[i^k].second + ws[d]));
            else
                dp[i] = std::min(dp[i], std::make_pair(dp[i^k].first + 1, ws[d]));
        }
    }

    std::cout << 1 + dp.back().first;

    return 0;
}
