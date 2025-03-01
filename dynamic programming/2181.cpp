#include <iostream>
#include <vector>

constexpr unsigned M = 1'000'000'007;

unsigned count(unsigned n, unsigned m)
{
    using integer = unsigned long long;

    const unsigned k = 1 << n;

    std::vector<std::vector<std::vector<integer>>> dp(1+m, std::vector<std::vector<integer>>(1+n+1, std::vector<integer>(k)));
    {
        dp[0][0][0] = 1;

        for (unsigned i = 0; i < m; ++i) {
            for (unsigned j = 0; j < n; ++j) {
                for (unsigned p = 0; p < k; ++p) {
                    const unsigned x = 1 << j;

                    dp[i][j+1][p^x] += dp[i][j][p];

                    if ((p & x) == 0 && (p & x << 1) == 0)
                        dp[i][j+2][p] += dp[i][j][p];
                }
            }

            for (unsigned p = 0; p < k; ++p)
                dp[i+1][0][p] = dp[i][n][p] % M;
        }
    }
    return dp[m][0][0];
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    unsigned n, m;
    std::cin >> n >> m;

    std::cout << count(n, m) << '\n';

    return 0;
}
