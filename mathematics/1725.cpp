#include <iostream>
#include <vector>

int main()
{
    unsigned n, a, b;
    std::cin >> n >> a >> b;

    std::vector<std::vector<double>> ps(n, std::vector<double>(1 + 6 * n));
    for (unsigned k = 1; k <= 6; ++k)
        ps[0][k] = 1.0 / 6;

    for (unsigned i = 1; i < n; ++i) {
        for (unsigned j = 1; j <= 6 * n; ++j) {
            for (unsigned k = 1; k <= 6; ++k)
                ps[i][j+k] += ps[i-1][j] / 6;
        }
    }

    double p = 0;
    for (unsigned i = a; i <= b; ++i)
        p += ps[n-1][i];

    std::cout << std::fixed << p;

    return 0;
}
