#include <iostream>
#include <vector>

std::string query(const std::string& b)
{
    std::cout << '?' << ' ' << b << std::endl;

    std::string r;
    std::cin >> r;
    return r;
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    unsigned n;
    std::cin >> n;

    std::vector<unsigned> p(n);
    for (unsigned i = 0; i < 10; ++i) {
        const unsigned mask = 1 << i;

        std::string b(n, '0');
        for (unsigned j = 0; j < n; ++j) {
            if ((j & mask) != 0)
                b[j] = '1';
        }

        const std::string r = query(b);
        for (unsigned j = 0; j < n; ++j) {
            if (r[j] == '1')
                p[j] += mask;
        }
    }

    std::cout << '!';
    for (const unsigned x : p)
        std::cout << ' ' << 1+x;

    return 0;
}
