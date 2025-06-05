#include <iostream>
#include <string>
#include <vector>

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    unsigned n;
    std::cin >> n;

    std::vector<std::string> grid(n);
    for (unsigned i = 0; i < n; ++i)
        std::cin >> grid[i];

    std::string s;
    {
        std::vector<std::pair<unsigned, unsigned>> q;
        q.emplace_back(0, 0);
        for (unsigned i = 2; i < 2 * n; ++i) {
            char c = 'Z';
            for (auto it = q.begin(); it != q.end(); ++it) {
                if (it->second + 1 < n)
                    c = std::min(c, grid[it->first][it->second + 1]);

                if (it->first + 1 < n)
                    c = std::min(c, grid[it->first + 1][it->second]);
            }
            s.push_back(c);

            std::vector<std::pair<unsigned, unsigned>> p;
            for (auto it = q.begin(); it != q.end(); ++it) {
                if (it->second + 1 < n && grid[it->first][it->second + 1] == c) {
                    p.emplace_back(it->first, it->second + 1);
                    grid[it->first][it->second + 1] = ' ';
                }
                if (it->first + 1 < n && grid[it->first + 1][it->second] == c) {
                    p.emplace_back(it->first + 1, it->second);
                    grid[it->first + 1][it->second] = ' ';
                }
            }
            std::swap(q, p);
        }
    }
    std::cout << grid[0][0] << s << '\n';

    return 0;
}
