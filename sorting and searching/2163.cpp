#include <iostream>
#include <vector>

unsigned lsb(unsigned index)
{
    return index & -index;
}

unsigned msb(unsigned index)
{
    return 1 << (__builtin_clz(1) - __builtin_clz(index));
}

int main()
{
    unsigned n, k;
    std::cin >> n >> k;

    std::vector<unsigned> ring(1 + n, 1);
    for (unsigned i = 1; i <= n; ++i) {
        const unsigned index = i + lsb(i);
        if (index <= n)
            ring[index] += ring[i];
    }

    const auto decrease = [&](unsigned index) {
        for (unsigned i = 1 + index; i <= n; i += lsb(i))
            --ring[i];
    };

    const auto search = [&](unsigned target_sum) {
        unsigned index = 0;
        for (unsigned i = msb(1 + n); i != 0; i >>= 1) {
            if (index + i <= n && ring[index + i] <= target_sum) {
                target_sum -= ring[index + i];
                index += i;
            }
        }
        return index;
    };

    unsigned index = 0;
    for (unsigned i = 0; i < n; ++i) {
        index = (index + k) % (n - i);

        const unsigned position = search(index);
        std::cout << 1 + position << ' ';
        decrease(position);
    }

    return 0;
}
