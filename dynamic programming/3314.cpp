#include <algorithm>
#include <iostream>
#include <vector>

unsigned solve(const std::vector<unsigned>& hs)
{
    const unsigned n = hs.size();

    std::vector<int> p(n);
    {
        std::vector<std::pair<unsigned, unsigned>> q;
        for (unsigned i = 0; i < n; ++i) {
            while (!q.empty() && q.back().first <= hs[i])
                q.pop_back();

            p[i] = (q.empty() ? -1 : q.back().second);
            q.emplace_back(hs[i], i);
        }
    }

    std::vector<int> s(n);
    {
        std::vector<std::pair<unsigned, unsigned>> q;
        for (unsigned i = n-1; ~i != 0; --i) {
            while (!q.empty() && q.back().first <= hs[i])
                q.pop_back();

            s[i] = (q.empty() ? -1 : q.back().second);
            q.emplace_back(hs[i], i);
        }
    }

    std::vector<unsigned> order(n);
    for (unsigned i = 0; i < n; ++i)
        order[i] = i;

    std::sort(order.begin(), order.end(), [&](unsigned i, unsigned j) {
        return hs[i] < hs[j];
    });

    std::vector<unsigned> c(n, 1);
    for (const unsigned x : order) {
        if (p[x] != -1)
            c[p[x]] = std::max(c[p[x]], c[x] + 1);

        if (s[x] != -1)
            c[s[x]] = std::max(c[s[x]], c[x] + 1);
    }

    return *std::max_element(c.begin(), c.end());
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    unsigned n;
    std::cin >> n;

    std::vector<unsigned> hs(n);
    for (unsigned i = 0; i < n; ++i)
        std::cin >> hs[i];

    std::cout << solve(hs) << '\n';

    return 0;
}
