#include <deque>
#include <iostream>
#include <vector>

using integer = unsigned long long;

template <typename T, typename F>
class MonotonicQueue {
public:
    MonotonicQueue() = default;

    explicit MonotonicQueue(F&& filter)
        : filter_(std::move(filter))
    {}

    void enqueue(T x)
    {
        while (!data_.empty() && filter_(data_.back().first, x))
            data_.pop_back();

        data_.emplace_back(x, enqueue_count_++);
    }

    void dequeue()
    {
        if (!data_.empty() && data_.front().second == dequeue_count_++)
            data_.pop_front();
    }

    T front() const
    {
        return data_.front().first;
    }

private:
    F filter_;

    std::deque<std::pair<T, unsigned>> data_;

    unsigned enqueue_count_ = 0;
    unsigned dequeue_count_ = 0;

}; // class MonotonicQueue<T, F>

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

    MonotonicQueue<integer, std::greater<integer>> q;
    for (unsigned i = 0; i < k; ++i)
        q.enqueue(v[i]);

    integer sum = q.front();
    for (unsigned i = k; i < n; ++i) {
        q.enqueue(v[i]);
        q.dequeue();

        sum ^= q.front();
    }

    std::cout << sum << '\n';

    return 0;
}
