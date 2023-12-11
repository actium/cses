#include <algorithm>
#include <iostream>
#include <vector>

int main()
{
    unsigned n;
    std::cin >> n;

    std::vector<std::pair<unsigned, unsigned>> tasks(n);
    for (unsigned i = 0; i < n; ++i)
        std::cin >> tasks[i].first >> tasks[i].second;

    std::sort(tasks.begin(), tasks.end());

    long long v = 0, t = 0;
    for (unsigned i = 0; i < n; ++i) {
        t += tasks[i].first;
        v += tasks[i].second - t;
    }

    std::cout << v;

    return 0;
}
