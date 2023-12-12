#include <iostream>
#include <vector>

int main()
{
    unsigned n;
    std::cin >> n;

    std::vector<int> xs(n);
    for (unsigned i = 0; i < n; ++i)
        std::cin >> xs[i];

    std::vector<std::vector<long long>> scores(n+1, std::vector<long long>(n+1));
    for (unsigned t = n - 1; ~t != 0; --t) {
        for (unsigned lb = 0; lb <= t; ++lb) {
            const unsigned ub = n - (t - lb);
            if (t % 2 == 0)
                scores[t][lb] = std::max(xs[lb] + scores[t+1][lb+1], xs[ub-1] + scores[t+1][lb]);
            else
                scores[t][lb] = std::min(scores[t+1][lb+1], scores[t+1][lb]);
        }
    }

    std::cout << scores[0][0];

    return 0;
}
