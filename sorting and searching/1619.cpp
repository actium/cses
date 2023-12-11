#include <algorithm>
#include <iostream>
#include <vector>

int main()
{
    unsigned n;
    std::cin >> n;

    std::vector<std::pair<unsigned, int>> events(2 * n);
    for (unsigned i = 0; i < n; ++i) {
        std::cin >> events[i*2].first >> events[i*2+1].first;

        events[i*2].second = +1;
        events[i*2+1].second = -1;
    }

    std::sort(events.begin(), events.end());

    unsigned k = 0, q = 0;
    for (const auto& e : events) {
        k += e.second;
        q = std::max(q, k);
    }

    std::cout << q;

    return 0;
}
