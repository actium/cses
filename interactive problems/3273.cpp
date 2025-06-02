#include <iostream>

char query(unsigned i)
{
    std::cout << '?' << ' ' << i << std::endl;

    char r;
    std::cin >> r;
    return r;
}

void solve(unsigned n)
{
    unsigned lb = 0, ub = n;
    for (char x = query(1); ub - lb > 1; ) {
        const unsigned mid = (lb + ub) / 2;

        const char c = query(mid+1);
        if ((c == x) == ((mid - lb) % 2 == 0)) {
            lb = mid;
            x = c;
        } else {
            ub = mid;
        }
    }

    std::cout << '!' << ' ' << ub << std::endl;
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    unsigned n;
    std::cin >> n;

    solve(n);

    return 0;
}
