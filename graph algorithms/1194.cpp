#include <iostream>
#include <queue>
#include <string>
#include <vector>

struct State {
    unsigned row;
    unsigned column;
    char actor;
};

void solve(std::vector<std::string>& map)
{
    const unsigned n = map.size(), m = map[0].size();

    std::queue<State> q;
    for (unsigned i = 0; i < n; ++i) {
        for (unsigned j = 0; j < m; ++j) {
            if (map[i][j] == 'M')
                q.push({ i, j, 'M' });
        }
    }
    for (unsigned i = 0; i < n; ++i) {
        for (unsigned j = 0; j < m; ++j) {
            if (map[i][j] == 'A')
                q.push({ i, j, 'A' });
        }
    }

    const auto paint = [&](unsigned r, unsigned c, char x, char d) {
        if (r < n && c < m && map[r][c] == '.') {
            map[r][c] = (x == 'A' ? d : 'M');
            q.push({ r, c, x });
        }
    };

    while (!q.empty()) {
        for (unsigned i = 0, k = q.size(); i < k; ++i) {
            const State s = q.front();
            q.pop();

            if ((s.row == 0 || s.row == n-1 || s.column == 0 || s.column == m-1) && s.actor == 'A') {
                std::string path;
                for (unsigned r = s.row, c = s.column; map[r][c] != 'A'; ) {
                    path.push_back(map[r][c]);

                    switch (map[r][c]) {
                        case 'U': ++r; break;
                        case 'R': --c; break;
                        case 'D': --r; break;
                        case 'L': ++c; break;
                    }
                }

                std::cout << "YES" << '\n';
                std::cout << path.length() << '\n';
                std::cout << std::string(path.rbegin(), path.rend()) << '\n';
                return;
            }

            paint(s.row-1, s.column, s.actor, 'U');
            paint(s.row+1, s.column, s.actor, 'D');
            paint(s.row, s.column-1, s.actor, 'L');
            paint(s.row, s.column+1, s.actor, 'R');
        }
    }

    std::cout << "NO" << '\n';
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    unsigned n, m;
    std::cin >> n >> m;

    std::vector<std::string> map(n);
    for (unsigned i = 0; i < n; ++i)
        std::cin >> map[i];

    solve(map);

    return 0;
}
