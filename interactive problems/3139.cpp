#include <iostream>
#include <vector>

bool query(unsigned i, unsigned j)
{
    std::cout << '?' << ' ' << i << ' ' << j << std::endl;

    std::string r;
    std::cin >> r;
    return r == "YES";
}

void solve(unsigned n)
{
    std::vector<unsigned> q;
    for (unsigned x = 1; x <= n; ++x) {
        int lb = -1, ub = q.size();
        while (ub - lb > 1) {
            const unsigned mid = (lb + ub) / 2;
            (query(x, q[mid]) ? ub : lb) = mid;
        }

        q.insert(q.begin() + ub, x);
    }

    std::vector<unsigned> p(n);
    for (unsigned i = 0; i < n; ++i)
        p[q[i]-1] = i + 1;

    std::cout << '!';
    for (const unsigned x : p)
        std::cout << ' ' << x;

    std::cout << std::endl;
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    unsigned n;
    std::cin >> n;

    solve(n);

    return 0;
}
