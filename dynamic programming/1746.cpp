#include <iostream>
#include <vector>

constexpr unsigned M = 1000000007;

int main()
{
    unsigned n, m;
    std::cin >> n >> m;

    std::vector<unsigned> xs(n);
    for (unsigned i = 0; i < n; ++i)
        std::cin >> xs[i];

    std::vector<std::vector<unsigned>> counts(n, std::vector<unsigned>(1+m+1));
    for (unsigned j = 1; j <= m; ++j)
        counts[0][j] = (xs[0] == 0 || j == xs[0]);

    for (unsigned i = 1; i < n; ++i) {
        if (xs[i] != 0) {
            const unsigned j = xs[i];
            counts[i][j] = (counts[i-1][j-1] + counts[i-1][j] + counts[i-1][j+1]) % M;
        } else {
            for (unsigned j = 1; j <= m; ++j)
                counts[i][j] = (counts[i-1][j-1] + counts[i-1][j] + counts[i-1][j+1]) % M;
        }
    }

    unsigned k = 0;
    for (unsigned i = 1; i <= m; ++i)
        k = (k + counts[n-1][i]) % M;

    std::cout << k;

    return 0;
}
