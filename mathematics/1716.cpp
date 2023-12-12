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

unsigned x[2000000];
unsigned y[1000001];

void initialize()
{
    x[0] = 1;
    y[0] = 1;

    for (unsigned i = 1; i <= 1000000; ++i) {
        x[i] = 1ull * x[i-1] * i % M;
        y[i] = raise(x[i], M - 2);
    }

    for (unsigned i = 1000001; i < 2000000; ++i)
        x[i] = 1ull * x[i-1] * i % M;
}

unsigned C(unsigned a, unsigned b)
{
    return 1ull * x[a] * y[b] % M * y[a-b] % M;
}

int main()
{
    initialize();

    unsigned n, m;
    std::cin >> n >> m;

    std::cout << C(n + m - 1, m);

    return 0;
}
