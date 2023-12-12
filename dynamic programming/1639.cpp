#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

constexpr unsigned oo = ~1u;

int main()
{
    std::string s, t;
    std::cin >> s >> t;

    const unsigned n = s.length(), m = t.length();

    std::vector<std::vector<unsigned>> distances(1+n, std::vector<unsigned>(1+m, oo));
    distances[0][0] = 0;
    for (unsigned i = 0; ++i <= n; distances[i][0] = i);
    for (unsigned j = 0; ++j <= m; distances[0][j] = j);
    for (unsigned i = 1; i <= n; ++i) {
        for (unsigned j = 1; j <= m; ++j) {
            if (s[i-1] == t[j-1])
                distances[i][j] = distances[i-1][j-1];

            const unsigned v = std::min({ distances[i-1][j-1], distances[i-1][j], distances[i][j-1] }) + 1;
            distances[i][j] = std::min(distances[i][j], v);
        }
    }

    std::cout << distances[n][m];

    return 0;
}
