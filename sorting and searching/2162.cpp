#include <iostream>
#include <vector>

int main()
{
    unsigned n;
    std::cin >> n;

    std::vector<unsigned> cs(n);
    for (unsigned i = 0; i < n; ++i)
        cs[i] = i + 1;

    for (unsigned i = 1; !cs.empty(); ) {
        std::vector<unsigned> b;
        for (const unsigned x : cs) {
            if (i++ % 2 == 1) {
                b.push_back(x);
            } else {
                std::cout << x << ' ';
            }
        }

        std::swap(cs, b);
    }

    return 0;
}
