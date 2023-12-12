#include <iostream>
#include <vector>

constexpr unsigned oo = ~1u;

int main()
{
    unsigned a, b;
    std::cin >> a >> b;

    std::vector<std::vector<unsigned>> counts(1+a, std::vector<unsigned>(1+b, oo));
    for (unsigned i = 1; i <= a; ++i) {
        for (unsigned j = 1; j <= b; ++j) {
            if (i == j)
                counts[i][j] = 0;

            for (unsigned k = 1; k < i; ++k)
                counts[i][j] = std::min(counts[i][j], counts[k][j] + counts[i-k][j] + 1);

            for (unsigned k = 1; k < j; ++k)
                counts[i][j] = std::min(counts[i][j], counts[i][k] + counts[i][j-k] + 1);
        }
    }

    std::cout << counts[a][b];

    return 0;
}
