#include <iostream>
#include <vector>

int main()
{
    unsigned n, m;
    std::cin >> n >> m;

    std::vector<unsigned> xs(1 + n);
    for (unsigned i = 1; i <= n; ++i)
        std::cin >> xs[i];

    std::vector<unsigned> ps(1 + n);
    for (unsigned i = 1; i <= n; ++i)
        ps[xs[i]] = i;

    unsigned k = 1;
    for (unsigned i = 1; i < n; ++i)
        k += (ps[i] > ps[i+1]);

    const auto update = [&](unsigned a, unsigned b, int d) {
        if (xs[a] != 1 && ps[xs[a]-1] > ps[xs[a]])
            k += d;

        if (xs[a] != n && ps[xs[a]] > ps[xs[a]+1])
            k += d;

        if (xs[b] != 1 && ps[xs[b]-1] > ps[xs[b]] && (xs[a] == n || ps[xs[b]] != ps[xs[a]+1]))
            k += d;

        if (xs[b] != n && ps[xs[b]] > ps[xs[b]+1] && (xs[a] == 1 || ps[xs[b]] != ps[xs[a]-1]))
            k += d;
    };

    for (unsigned i = 0; i < m; ++i) {
        unsigned a, b;
        std::cin >> a >> b;

        if (a != b) {
            update(a, b, -1);

            std::swap(xs[a], xs[b]);
            std::swap(ps[xs[a]], ps[xs[b]]);

            update(a, b, +1);
        }

        std::cout << k << '\n';
    }

    return 0;
}
