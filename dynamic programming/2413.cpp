#include <iostream>
#include <vector>

constexpr unsigned N = 1000000, M = 1000000007;

unsigned counts[6][1+N];

void prepare()
{
    // 0: | | |
    // 1: | |-|
    // 2: |-| |
    // 3: |-|-|
    // 4: |---|
    // 5: |   |

    counts[4][0] = 1;

    for (unsigned i = 1; i <= N; ++i) {
        const unsigned u = (0ull + counts[0][i-1] + counts[1][i-1] + counts[2][i-1] + counts[3][i-1] + counts[4][i-1]) % M;
        counts[0][i] = u;
        counts[1][i] = u;
        counts[2][i] = u;
        counts[3][i] = u;

        const unsigned v = (counts[3][i-1] + counts[4][i-1] + counts[5][i-1]) % M;
        counts[4][i] = v;
        counts[5][i] = v;
    }
}

void solve(unsigned n)
{
    std::cout << (counts[3][n] + counts[4][n]) % M << '\n';
}

void test_case()
{
    unsigned n;
    std::cin >> n;

    solve(n);
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    prepare();

    size_t t;
    std::cin >> t;

    while (t-- > 0)
        test_case();

    return 0;
}
