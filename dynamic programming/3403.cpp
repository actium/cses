#include <iostream>
#include <vector>

void backtrack(const std::vector<unsigned>& as, const std::vector<unsigned>& bs, const std::vector<std::vector<unsigned>>& dp,
    unsigned i, unsigned j, std::vector<unsigned>& s)
{
    if (i == 0 || j == 0)
        return;

    if (as[i-1] == bs[j-1]) {
        backtrack(as, bs, dp, i-1, j-1, s);
        s.push_back(as[i-1]);
        return;
    }

    if (dp[i-1][j] > dp[i][j-1]) {
        backtrack(as, bs, dp, i-1, j, s);
    } else {
        backtrack(as, bs, dp, i, j-1, s);
    }
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    unsigned n, m;
    std::cin >> n >> m;

    std::vector<unsigned> as(n);
    for (unsigned i = 0; i < n; ++i)
        std::cin >> as[i];

    std::vector<unsigned> bs(m);
    for (unsigned i = 0; i < m; ++i)
        std::cin >> bs[i];

    std::vector<std::vector<unsigned>> dp(1+n, std::vector<unsigned>(1+m));
    for (unsigned i = 1; i <= n; ++i) {
        for (unsigned j = 1; j <= m; ++j) {
            if (as[i-1] == bs[j-1])
                dp[i][j] = dp[i-1][j-1] + 1;
            else
                dp[i][j] = std::max(dp[i-1][j], dp[i][j-1]);
        }
    }

    std::vector<unsigned> s;
    backtrack(as, bs, dp, n, m, s);

    std::cout << s.size() << '\n';
    for (const unsigned x : s)
        std::cout << x << ' ';

    return 0;
}
