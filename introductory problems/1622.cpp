#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

int main()
{
    std::string s;
    std::cin >> s;

    std::sort(s.begin(), s.end());

    std::vector<std::string> v;
    do {
        v.push_back(s);
    } while (std::next_permutation(s.begin(), s.end()));

    std::cout << v.size() << '\n';
    for (const auto& s : v)
        std::cout << s << '\n';

    return 0;
}
