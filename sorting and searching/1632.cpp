#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

int main()
{
    unsigned n, k;
    std::cin >> n >> k;

    std::vector<std::pair<unsigned, unsigned>> intervals(n);
    for (unsigned i = 0; i < n; ++i)
        std::cin >> intervals[i].first >> intervals[i].second;

    std::sort(intervals.begin(), intervals.end(), [](const auto& a, const auto& b) {
        return a.second < b.second;
    });

    unsigned c = 0;

    std::multiset<unsigned> q;
    for (const auto& i : intervals) {
        if (q.size() == k && i.first < *q.begin())
            continue;

        const auto it = q.lower_bound(i.first);
        if (it != q.begin() && *std::prev(it) <= i.first) {
            q.erase(std::prev(it));
        } else if (it != q.end() && *it == i.first) {
            q.erase(it);
        }

        q.insert(i.second);

        ++c;
    }

    std::cout << c;

    return 0;
}
