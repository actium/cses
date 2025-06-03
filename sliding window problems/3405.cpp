#include <iostream>
#include <vector>

using integer = unsigned long long;

template <typename T, typename F>
class SlidingWindowAggregation {
public:
    SlidingWindowAggregation() = default;

    explicit SlidingWindowAggregation(F&& operation)
        : operation_(std::move(operation))
    {}

    void enqueue(T x)
    {
        push(stacks_[0], x);
    }

    void dequeue()
    {
        if (stacks_[1].empty()) {
            while (!stacks_[0].empty()) {
                push(stacks_[1], stacks_[0].back().first);
                stacks_[0].pop_back();
            }
        }
        stacks_[1].pop_back();
    }

    T operator ()() const
    {
        if (stacks_[1].empty())
            return stacks_[0].back().second;

        if (stacks_[0].empty())
            return stacks_[1].back().second;

        return operation_(stacks_[0].back().second, stacks_[1].back().second);
    }

private:
    void push(std::vector<std::pair<T, T>>& stack, T x)
    {
        stack.emplace_back(x, stack.empty() ? x : operation_(stack.back().second, x));
    }

private:
    F operation_;

    std::vector<std::pair<T, T>> stacks_[2];

}; // class SlidingWindowAggregation<T, F>

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    unsigned n, k;
    std::cin >> n >> k;

    unsigned x, a, b, c;
    std::cin >> x >> a >> b >> c;

    std::vector<integer> v(n);
    {
        v[0] = x;
        for (unsigned i = 1; i < n; ++i)
            v[i] = (a * v[i-1] + b) % c;
    }

    SlidingWindowAggregation<integer, std::bit_or<integer>> swa;
    for (unsigned i = 0; i < k; ++i)
        swa.enqueue(v[i]);

    integer sum = swa();
    for (unsigned i = k; i < n; ++i) {
        swa.enqueue(v[i]);
        swa.dequeue();

        sum ^= swa();
    }

    std::cout << sum << '\n';

    return 0;
}
