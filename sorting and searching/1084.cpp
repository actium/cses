#include <algorithm>
#include <iostream>
#include <vector>

int main()
{
    unsigned n, m, k;
    std::cin >> n >> m >> k;

    std::vector<unsigned> a(n);
    for (unsigned i = 0; i < n; ++i)
        std::cin >> a[i];

    std::vector<unsigned> b(m);
    for (unsigned i = 0; i < m; ++i)
        std::cin >> b[i];

    std::sort(a.begin(), a.end());
    std::sort(b.begin(), b.end());

    unsigned c = 0;
    for (unsigned i = 0, j = 0; i < n; ++i) {
        while (j < m && b[j] + k < a[i])
            ++j;

        if (j < m && b[j] <= a[i] + k) {
            ++c;
            ++j;
        }
    }

    std::cout << c;

    return 0;
}
