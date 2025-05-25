#include <iostream>

bool check(unsigned q)
{
    std::cout << '?' << ' ' << q << std::endl;

    std::string s;
    std::cin >> s;
    return s == "YES";
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    unsigned lb = 0, ub = 1000000000;
    while (ub - lb > 1) {
        const unsigned mid = (lb + ub) / 2;
        (check(mid) ? lb : ub) = mid;
    }

    std::cout << '!' << ' ' << ub << '\n';

    return 0;
}
