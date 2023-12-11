#include <array>
#include <iostream>
#include <string>

bool paint(std::array<std::string, 8>& s, unsigned y, unsigned x, char a, char b)
{
    const auto repaint = [&](unsigned r, unsigned c) {
        if (r <= 7 && c <= 7) {
            if (s[r][c] != a && isalpha(s[r][c]) && isupper(s[r][c]))
                return false;

            if (s[r][c] == a)
                s[r][c] = b;
        }
        return true;
    };

    for (int d = -8; d < 8; ++d) {
        if (d == 0)
            continue;

        if (!repaint(y, x + d) || !repaint(y + d, x))
            return false;

        if (!repaint(y + d, x + d) || !repaint(y + d, x - d))
            return false;
    }
    s[y][x] = isalpha(b) ? toupper(b) : b;
    return true;
}

unsigned count_ways(const std::array<std::string, 8>& b, std::array<std::string, 8>& s, unsigned y)
{
    if (y == 8)
        return 1;

    unsigned k = 0;
    for (unsigned x = 0; x < 8; ++x) {
        if (s[y][x] != ' ' || b[y][x] == '*')
            continue;

        if (paint(s, y, x, ' ', 'a' + y))
            k += count_ways(b, s, y + 1);

        paint(s, y, x, 'a' + y, ' ');
    }
    return k;
}

int main()
{
    std::array<std::string, 8> b;
    for (unsigned i = 0; i < 8; ++i)
        std::cin >> b[i];

    std::array<std::string, 8> s;
    for (unsigned i = 0; i < 8; ++i)
        s[i].resize(8, ' ');

    std::cout << count_ways(b, s, 0);

    return 0;
}
