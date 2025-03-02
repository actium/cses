#include <iostream>
#include <string>

using integer = unsigned long long;

integer count(const std::string& s)
{
    const unsigned m = s.length();

    integer dp[20][10][2] = {};
    for (unsigned i = 1; i < m; ++i)
        dp[i][0][0] = 1;

    dp[0][0][1] = 1;
    for (unsigned i = 0; i < m; ++i) {
        for (unsigned d = 0; d < 10; ++d) {
            for (unsigned e = 0; e < 10; ++e) {
                if (e == d)
                    continue;

                dp[i+1][e][0] += dp[i][d][0];

                if (e < s[i] - '0')
                    dp[i+1][e][0] += dp[i][d][1];

                if (e == s[i] - '0')
                    dp[i+1][e][1] += dp[i][d][1];
            }
        }
    }

    integer k = 1;
    for (unsigned i = 0; i < 10; ++i)
        k += dp[m][i][0] + dp[m][i][1];

    return k;
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    integer a, b;
    std::cin >> a >> b;

    std::cout << count(std::to_string(b)) - (a != 0 ? count(std::to_string(a-1)) : 0) << '\n';

    return 0;
}
