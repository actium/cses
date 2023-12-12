#include <functional>
#include <iostream>
#include <vector>

template <typename T, typename F = std::function<T(T, T)>>
class RangeQueryTable {
public:
    template <typename Iterator>
    explicit RangeQueryTable(Iterator lb, Iterator ub, F&& combine)
        : combine_(combine)
    {
        const unsigned n = ub - lb;

        data_.reserve(w - __builtin_clz(n) + 1);
        data_.emplace_back(lb, ub);
        for (unsigned i = 1; (1u << i) <= n; ++i) {
            const unsigned k = n - (1 << i) + 1;

            data_.emplace_back(k);
            for (unsigned j = 0; j < k; ++j)
                data_[i][j] = combine_(data_[i-1][j], data_[i-1][j+(1 << (i - 1))]);
        }
    }

    template <bool cascading>
    T query(unsigned lb, unsigned ub) const
    {
        unsigned x = w - __builtin_clz(ub - lb);

        T value = data_[x][lb];
        if constexpr (!cascading) {
            value = combine_(value, data_[x][ub - (1 << x)]);
        } else {
            for (lb += 1 << x; lb < ub; lb += 1 << x) {
                x = w - __builtin_clz(ub - lb);
                value = combine_(value, data_[x][lb]);
            }
        }
        return value;
    }

private:
    const F combine_;

    std::vector<std::vector<T>> data_;

    static constexpr unsigned w = __builtin_clz(1);

}; // class RangeQueryTable<T, F>

int main()
{
    unsigned n, q;
    std::cin >> n >> q;

    std::vector<unsigned> xs(n);
    for (unsigned i = 0; i < n; ++i)
        std::cin >> xs[i];

    const RangeQueryTable<unsigned> rqt(xs.begin(), xs.end(), [](unsigned a, unsigned b) {
        return std::min(a, b);
    });

    for (unsigned i = 0; i < q; ++i) {
        unsigned a, b;
        std::cin >> a >> b;

        std::cout << rqt.query<false>(a-1, b) << '\n';
    }

    return 0;
}
