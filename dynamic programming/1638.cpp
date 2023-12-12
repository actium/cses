#include <iostream>
#include <string>
#include <vector>

constexpr unsigned M = 1000000007;

int main()
{
    unsigned n;
    std::cin >> n;

    std::vector<std::string> grid(n);
    for (unsigned i = 0; i < n; ++i)
        std::cin >> grid[i];

    std::vector<std::vector<unsigned>> counts(n, std::vector<unsigned>(n));
    counts[0][0] = 1;
    for (unsigned i = 0; i < n; ++i) {
        for (unsigned j = 0; j < n; ++j) {
            if (i > 0)
                counts[i][j] += counts[i-1][j];

            if (j > 0)
                counts[i][j] += counts[i][j-1];

            if (grid[i][j] == '*')
                counts[i][j] = 0;

            counts[i][j] %= M;
        }
    }

    std::cout << counts[n-1][n-1];

    return 0;
}
