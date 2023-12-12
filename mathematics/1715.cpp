#include <iostream>
#include <string>

constexpr unsigned M = 1000000007;

unsigned raise(unsigned base, unsigned power)
{
    unsigned v = 1;
    for (unsigned long long b = base; power != 0; power /= 2) {
        if (power % 2 == 1)
            v = v * b % M;

        b = b * b % M;
    }
    return v;
}

unsigned x[1000001];
unsigned y[1000001];

void initialize()
{
    x[0] = 1;
    y[0] = 1;

    for (unsigned i = 1; i <= 1000000; ++i) {
        x[i] = 1ull * x[i-1] * i % M;
        y[i] = raise(x[i], M - 2);
    }
}

int main()
{
    initialize();

    std::string s;
    std::cin >> s;

    unsigned fs[26] = {};
    for (const char c : s)
        ++fs[c - 'a'];

    unsigned k = x[s.length()];
    for (const unsigned f : fs) {
        if (f != 0)
            k = 1ull * k * y[f] % M;
    }

    std::cout << k;

    return 0;
}
