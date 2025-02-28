#include <iostream>
#include <vector>

using integer = unsigned long long;

constexpr unsigned M = 1000000;

class Sieve {
public:
    explicit Sieve(unsigned upper_bound)
        : upper_bound_(upper_bound)
        , smallest_prime_factors_(1 + upper_bound)
    {
        std::vector<unsigned> primes;
        for (unsigned i = 2; i <= upper_bound_; ++i) {
            if (smallest_prime_factors_[i] == 0) {
                smallest_prime_factors_[i] = i;
                primes.push_back(i);
            }

            for (const unsigned p : primes) {
                if (p > smallest_prime_factors_[i] || i * p > upper_bound_)
                    break;

                smallest_prime_factors_[i * p] = p;
            }
        }
    }

    std::vector<unsigned> factorize_number(unsigned n) const
    {
        std::vector<unsigned> factors;
        while (n != 1) {
            factors.push_back(smallest_prime_factors_[n]);

            while (smallest_prime_factors_[n] == factors.back())
                n /= factors.back();
        }
        return factors;
    }

private:
    const unsigned upper_bound_;

    std::vector<unsigned> smallest_prime_factors_;

}; // class Sieve

integer count(const std::vector<unsigned>& xs)
{
    integer q = xs.size() * (xs.size() - 1ull) / 2;
    {
        const Sieve sieve(M);

        unsigned f[1+M] = {};
        for (const unsigned x : xs) {
            const std::vector<unsigned> factors = sieve.factorize_number(x);

            integer h[2] = {};
            for (unsigned i = 1, m = 1 << factors.size(); i < m; ++i) {
                unsigned p = 1;
                for (unsigned j = i; j != 0; j &= j - 1)
                    p *= factors[__builtin_ctz(j)];

                h[__builtin_popcount(i) % 2] += f[p]++;
            }

            q -= h[1] - h[0];
        }
    }
    return q;
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    unsigned n;
    std::cin >> n;

    std::vector<unsigned> xs(n);
    for (unsigned i = 0; i < n; ++i)
        std::cin >> xs[i];

    std::cout << count(xs) << '\n';

    return 0;
}
