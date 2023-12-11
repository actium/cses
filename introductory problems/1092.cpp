#include <iostream>
#include <vector>

void solve(unsigned n)
{
    auto s = n * (n + 1ull) / 2;
    if (s % 2 != 0) {
        std::cout << "NO";
        return;
    }

    s /= 2;

    std::vector<unsigned> p[2];
    for (unsigned x = n; x > 0; --x) {
        if (x <= s) {
            p[0].push_back(x);
            s -= x;
        } else {
            p[1].push_back(x);
        }
    }

    std::cout << "YES" << '\n';
    for (const auto& v : p) {
        std::cout << v.size() << '\n';

        for (const auto x : v)
            std::cout << x << ' ';

        std::cout << '\n';
    }
}

int main()
{
    unsigned n;
    std::cin >> n;

    solve(n);

    return 0;
}
