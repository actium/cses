#include <algorithm>
#include <iostream>
#include <string>

int main()
{
    std::string s;
    std::cin >> s;

    const unsigned n = s.length();

    unsigned k[26] = {};
    for (unsigned i = 0, x = 0, c = 0; i < n; ++i) {
        if (s[i] != s[x]) {
            x = i;
            c = 0;
        }

        const unsigned label = s[i] - 'A';
        k[label] = std::max(k[label], ++c);
    }

    std::cout << *std::max_element(std::begin(k), std::end(k));

    return 0;
}
