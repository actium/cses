#include <iostream>
#include <map>
#include <vector>

void solve(const std::vector<unsigned>& as, unsigned x)
{
    const unsigned n = as.size();

    std::multimap<unsigned, std::pair<unsigned, unsigned>> ps;
    for (unsigned i = 1; i < n; ++i) {
        for (unsigned j = 0; j < i; ++j)
            ps.emplace(as[i] + as[j], std::make_pair(i + 1, j + 1));
    }

    for (const auto& p : ps) {
        if (p.first >= x)
            break;

        const auto r = ps.equal_range(x - p.first);
        for (auto it = r.first; it != r.second; ++it) {
            if (it->second.first == p.second.first || it->second.first == p.second.second)
                continue;

            if (it->second.second == p.second.first || it->second.second == p.second.second)
                continue;

            std::cout << it->second.first << ' ' << it->second.second << ' ' << p.second.first << ' ' << p.second.second;
            return;
        }
    }

    std::cout << "IMPOSSIBLE";
}

int main()
{
    unsigned n, x;
    std::cin >> n >> x;

    std::vector<unsigned> as(n);
    for (unsigned i = 0; i < n; ++i)
        std::cin >> as[i];

    solve(as, x);

    return 0;
}
