#include <iostream>
#include <vector>

void move_disks(unsigned n, unsigned s, unsigned t, unsigned u, std::vector<std::pair<unsigned, unsigned>>& moves)
{
    if (n == 0)
        return;

    move_disks(n - 1, s, u, t, moves);
    moves.emplace_back(s, t);
    move_disks(n - 1, u, t, s, moves);
}

int main()
{
    unsigned n;
    std::cin >> n;

    std::vector<std::pair<unsigned, unsigned>> moves;
    move_disks(n, 1, 3, 2, moves);

    std::cout << moves.size() << '\n';
    for (const auto& m : moves)
        std::cout << m.first << ' ' << m.second << '\n';

    return 0;
}
