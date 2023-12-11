#include <algorithm>
#include <iostream>
#include <vector>

int main()
{
    unsigned n, x;
    std::cin >> n >> x;

    std::vector<std::pair<unsigned, unsigned>> a(n);
    for (unsigned i = 0; i < n; ++i) {
        std::cin >> a[i].first;

        a[i].second = i + 1;
    }

    std::sort(a.begin(), a.end());

    unsigned i = 0, j = n - 1;
    while (i < j && a[i].first + a[j].first != x)
        a[i].first + a[j].first < x ? ++i : --j;

    if (i < j && a[i].first + a[j].first == x)
        std::cout << a[i].second << ' ' << a[j].second;
    else
        std::cout << "IMPOSSIBLE";

    return 0;
}