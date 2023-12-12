#include <iostream>
#include <string>
#include <vector>

void mark(std::vector<std::string>& map, unsigned i, unsigned j)
{
    if (i < map.size() && j < map[0].size() && map[i][j] == '.') {
        map[i][j] = '*';

        mark(map, i-1, j);
        mark(map, i, j+1);
        mark(map, i+1, j);
        mark(map, i, j-1);
    }
}

int main()
{
    unsigned n, m;
    std::cin >> n >> m;

    std::vector<std::string> map(n);
    for (unsigned i = 0; i < n; ++i)
        std::cin >> map[i];

    unsigned k = 0;
    for (unsigned i = 0; i < n; ++i) {
        for (unsigned j = 0; j < m; ++j) {
            if (map[i][j] == '.') {
                ++k;
                mark(map, i, j);
            }
        }
    }

    std::cout << k;

    return 0;
}
