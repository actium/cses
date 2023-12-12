#include <iostream>
#include <queue>
#include <string>
#include <vector>

using location_t = std::pair<unsigned, unsigned>;
using transition_t = std::pair<location_t, char>;

void solve(std::vector<std::string>& map, const location_t& a)
{
    const unsigned n = map.size(), m = map[0].size();

    std::vector<std::vector<transition_t>> ts(n, std::vector<transition_t>(m));

    const auto print_path = [&](const location_t& b) {
        std::string path;
        for (auto x = b; x != ts[x.first][x.second].first; x = ts[x.first][x.second].first)
            path.push_back(ts[x.first][x.second].second);

        std::cout << path.length() << '\n';
        for (auto it = path.rbegin(); it != path.rend(); ++it)
            std::cout << *it;
    };

    std::queue<location_t> q;

    const auto enqueue = [&](const location_t& x, const location_t& p, char direction) {
        if (x.first < n && x.second < m && (map[x.first][x.second] == '.' || isalpha(map[x.first][x.second]))) {
            q.push(x);

            if (map[x.first][x.second] == '.')
                map[x.first][x.second] = '*';

            ts[x.first][x.second].first = p;
            ts[x.first][x.second].second = direction;
        }
    };

    enqueue(a, a, ' ');
    while (!q.empty()) {
        const location_t x = q.front();
        q.pop();

        if (map[x.first][x.second] == 'B') {
            std::cout << "YES" << '\n';
            print_path(x);
            return;
        }

        map[x.first][x.second] = '#';

        enqueue({ x.first-1, x.second }, x, 'U');
        enqueue({ x.first, x.second+1 }, x, 'R');
        enqueue({ x.first+1, x.second }, x, 'D');
        enqueue({ x.first, x.second-1 }, x, 'L');
    }

    std::cout << "NO";
}

int main()
{
    unsigned n, m;
    std::cin >> n >> m;

    std::vector<std::string> map(n);
    for (unsigned i = 0; i < n; ++i)
        std::cin >> map[i];

    for (unsigned i = 0; i < n; ++i) {
        const auto j = map[i].find('A');
        if (j != std::string::npos) {
            solve(map, std::make_pair(i, j));
            break;
        }
    }

    return 0;
}
