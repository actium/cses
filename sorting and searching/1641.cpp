#include <algorithm>
#include <iostream>
#include <vector>

void solve(std::vector<std::pair<unsigned, unsigned>>& as, unsigned x)
{
    const unsigned n = as.size();

    std::sort(as.begin(), as.end());

    for (unsigned i = 0; i < n; ++i) {
        for (unsigned j = i + 1, k = n - 1; j < k; ) {
            const unsigned s = as[i].first + as[j].first + as[k].first;
            if (s == x) {
                std::cout << as[i].second << ' ' << as[j].second << ' ' << as[k].second;
                return;
            }

            s < x ? ++j : --k;
        }
    }

    std::cout << "IMPOSSIBLE";
}

int main()
{
    unsigned n, x;
    std::cin >> n >> x;

    std::vector<std::pair<unsigned, unsigned>> as(n);
    for (unsigned i = 0; i < n; ++i) {
        std::cin >> as[i].first;

        as[i].second = i + 1;
    }

    solve(as, x);

    return 0;
}
