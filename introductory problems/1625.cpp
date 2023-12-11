#include <array>
#include <iostream>
#include <string>

unsigned count_ways(std::array<std::string, 9>& g, const std::string& s, unsigned i, unsigned x, unsigned y, char d)
{
    if (x == 1 && y == 7)
        return i == 48;

    if (d == 'U' && g[y-1][x] != '.' && g[y][x-1] == '.' && g[y][x+1] == '.')
        return 0;

    if (d == 'R' && g[y][x+1] != '.' && g[y-1][x] == '.' && g[y+1][x] == '.')
        return 0;

    if (d == 'D' && g[y+1][x] != '.' && g[y][x-1] == '.' && g[y][x+1] == '.')
        return 0;

    if (d == 'L' && g[y][x-1] != '.' && g[y-1][x] == '.' && g[y+1][x] == '.')
        return 0;

    unsigned k = 0;
    {
        g[y][x] = '*';

        if (g[y-1][x] == '.' && (s[i] == '?' || s[i] == 'U'))
            k += count_ways(g, s, i+1, x, y-1, 'U');

        if (g[y][x+1] == '.' && (s[i] == '?' || s[i] == 'R'))
            k += count_ways(g, s, i+1, x+1, y, 'R');

        if (g[y+1][x] == '.' && (s[i] == '?' || s[i] == 'D'))
            k += count_ways(g, s, i+1, x, y+1, 'D');

        if (g[y][x-1] == '.' && (s[i] == '?' || s[i] == 'L'))
            k += count_ways(g, s, i+1, x-1, y, 'L');

        g[y][x] = '.';
    }
    return k;
}

int main()
{
    std::string s;
    std::cin >> s;

    std::array<std::string, 9> g = {
        "#########",
        "#.......#",
        "#.......#",
        "#.......#",
        "#.......#",
        "#.......#",
        "#.......#",
        "#.......#",
        "#########",
    };

    std::cout << count_ways(g, s, 0, 1, 1, ' ');

    return 0;
}
