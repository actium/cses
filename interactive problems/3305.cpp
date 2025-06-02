#include <iostream>
#include <vector>

std::vector<unsigned> scores[2];

unsigned query(unsigned x, unsigned i, unsigned n)
{
    if (i == 0)
        return ~0u;

    if (i > n)
        return 0;

    if (scores[x][i] == 0) {
        std::cout << "FS"[x] << ' ' << i << std::endl;
        std::cin >> scores[x][i];
    }
    return scores[x][i];
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    unsigned n, k;
    std::cin >> n >> k;

    for (unsigned t = 0; t < 2; ++t)
        scores[t].resize(1 + n);

    unsigned s = 0;
    for (unsigned t = 0; t < 2; ++t) {
        for (unsigned lb = 0, ub = std::min(k, n) + 1; ub - lb > 1 && s == 0; ) {
            const unsigned mid = (lb + ub) / 2;

            if (query(t^1, k-mid, n) < query(t, mid, n)) {
                lb = mid;
                continue;
            }
            if (query(t^1, k-mid+1, n) > query(t, mid, n)) {
                ub = mid;
                continue;
            }

            s = query(t, mid, n);
        }
    }

    std::cout << '!' << ' ' << s << std::endl;

    return 0;
}
