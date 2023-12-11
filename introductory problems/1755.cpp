#include <iostream>
#include <string>

int main()
{
    std::string s;
    std::cin >> s;

    unsigned f[26] = {};
    for (const char c : s)
        ++f[c - 'A'];

    std::string t, z;
    for (size_t i = 0; i < 26; ++i) {
        t.append(f[i] / 2, 'A' + i);

        if (f[i] % 2 == 1)
            z.push_back('A' + i);
    }

    if (z.size() > 1) {
        std::cout << "NO SOLUTION";
    }  else {
        std::cout << t << z << std::string(t.rbegin(), t.rend());
    }

    return 0;
}
