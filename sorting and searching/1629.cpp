#include <algorithm>
#include <iostream>
#include <vector>

int main()
{
    unsigned n;
    std::cin >> n;

    std::vector<std::pair<unsigned, unsigned>> intervals(n);
    for (unsigned i = 0; i < n; ++i)
        std::cin >> intervals[i].first >> intervals[i].second;

    std::sort(intervals.begin(), intervals.end(), [](const auto& a, const auto& b) {
        return a.second < b.second;
    });

    unsigned t = 0, k = 0;
    for (const auto& i : intervals) {
        if (i.first >= t) {
            ++k;
            t = i.second;
        }
    }

    std::cout << k;

    return 0;
}
