#include <iostream>

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

unsigned C(unsigned a, unsigned b)
{
    return 1ull * x[a] * y[b] % M * y[a-b] % M;
}

int main()
{
    initialize();

    unsigned n;
    std::cin >> n;

    for (unsigned i = 0; i < n; ++i) {
        unsigned a, b;
        std::cin >> a >> b;

        std::cout << C(a, b) << '\n';
    }

    return 0;
}
