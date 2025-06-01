#include <algorithm>
#include <iostream>
#include <vector>

template <typename T>
class BinaryIndexedTree {
public:
    explicit BinaryIndexedTree(unsigned size)
        : nodes_(1 + size)
    {}

    template <typename U>
    void update(unsigned index, U delta)
    {
        for (++index; index < nodes_.size(); index += index & -index)
            nodes_[index] += delta;
    }

    T sum(unsigned range_begin, unsigned range_end) const
    {
        auto sum = T();
        while (range_end > range_begin) {
            sum += nodes_[range_end];
            range_end &= range_end - 1;
        }
        while (range_begin > range_end) {
            sum -= nodes_[range_begin];
            range_begin &= range_begin - 1;
        }
        return sum;
    }

private:
    std::vector<T> nodes_;

}; // class BinaryIndexedTree<T>

struct Point {
    int x;
    int y;
};

std::istream& operator >>(std::istream& input, Point& p)
{
    return input >> p.x >> p.y;
}

struct Event {
    int time;
    unsigned type;
    unsigned index;
};

unsigned solve(std::vector<std::pair<Point, Point>>& segments)
{
    const unsigned n = segments.size();

    std::vector<Event> events;
    for (unsigned i = 0; i < n; ++i) {
        if (segments[i].first.x != segments[i].second.x) {
            events.push_back({ segments[i].first.x, 0, i });
            events.push_back({ segments[i].second.x, 2, i });
        } else {
            events.push_back({ segments[i].first.x, 1, i });
        }
    }

    std::sort(events.begin(), events.end(), [](const Event& lhs, const Event& rhs) {
        return lhs.time != rhs.time ? lhs.time < rhs.time : lhs.type < rhs.type;
    });

    unsigned k = 0;
    {
        BinaryIndexedTree<int> bit(2000002);
        for (const Event& e : events) {
            switch (e.type) {
                case 0:
                    bit.update(segments[e.index].first.y + 1000000, +1);
                    break;
                case 1:
                    k += bit.sum(segments[e.index].first.y + 1000000, segments[e.index].second.y + 1000001);
                    break;
                case 2:
                    bit.update(segments[e.index].second.y + 1000000, -1);
                    break;
            }
        }
    }
    return k;
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    unsigned n;
    std::cin >> n;

    std::vector<std::pair<Point, Point>> segments(n);
    for (unsigned i = 0; i < n; ++i)
        std::cin >> segments[i].first >> segments[i].second;

    std::cout << solve(segments) << '\n';

    return 0;
}
