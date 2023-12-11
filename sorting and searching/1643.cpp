#include <iostream>

int main()
{
    unsigned n;
    std::cin >> n;

    long long local_max = 0, global_max = -1000000000;
    for (unsigned i = 0; i < n; ++i) {
        int x;
        std::cin >> x;

        local_max = std::max<long long>(local_max + x, x);
        global_max = std::max(global_max, local_max);
    }

    std::cout << global_max;

    return 0;
}
