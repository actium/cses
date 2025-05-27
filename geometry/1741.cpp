#include <algorithm>
#include <deque>
#include <iostream>
#include <vector>

using integer = unsigned long long;

struct Node {
    unsigned range_size;
    unsigned value;
    unsigned count;

    explicit Node(unsigned range_size)
        : range_size(range_size)
        , value(0)
        , count(range_size)
    {}

    Node(const Node& lhs, const Node& rhs)
        : range_size(lhs.range_size + rhs.range_size)
        , value(std::min(lhs.value, rhs.value))
        , count(0)
    {
        if (lhs.value == value)
            count += lhs.count;

        if (rhs.value == value)
            count += rhs.count;
    }
};

class SparseSegmentTree {
    struct Range {
        int begin;
        int end;
    };

    class Segment {
    public:
        explicit Segment(const Range& range)
            : range_(range)
            , data_(range.end - range.begin)
        {}

        void update(const Range& range, int delta)
        {
            if (range.end <= range_.begin || range_.end <= range.begin)
                return;

            if (range.begin <= range_.begin && range_.end <= range.end) {
                aggregate_operation(delta);
            } else {
                propagate_operation();
                subsegments_[0]->update(range, delta);
                subsegments_[1]->update(range, delta);
                recompute_value();
            }
        }

        Node query(const Range& range)
        {
            if (range.end <= range_.begin || range_.end <= range.begin)
                return Node(0);

            if (range.begin <= range_.begin && range_.end <= range.end)
                return data_;

            propagate_operation();
            return Node(subsegments_[0]->query(range), subsegments_[1]->query(range));
        }

    private:
        void ensure_subsegments_exist()
        {
            static std::deque<Segment> segment_pool;

            const int mid_point = (range_.begin + range_.end) / 2;
            if (subsegments_[0] == nullptr)
                subsegments_[0] = &segment_pool.emplace_back(Range{range_.begin, mid_point});
            if (subsegments_[1] == nullptr)
                subsegments_[1] = &segment_pool.emplace_back(Range{mid_point, range_.end});
        }

        Segment* select_subsegment(size_t point) const
        {
            return subsegments_[point >= subsegments_[1]->range_.begin];
        }

        void aggregate_operation(int delta)
        {
            delta_ += delta;
            data_.value += delta;
        }

        void propagate_operation()
        {
            ensure_subsegments_exist();

            if (delta_ != 0) {
                subsegments_[0]->aggregate_operation(delta_);
                subsegments_[1]->aggregate_operation(delta_);
                delta_ = 0;
            }
        }

        void recompute_value()
        {
            data_ = Node(subsegments_[0]->data_, subsegments_[1]->data_);
        }

    private:
        const Range range_;

        Node data_;
        int delta_ = 0;

        Segment* subsegments_[2] = {};

    }; // class Segment

public:
    SparseSegmentTree(int range_begin, int range_end)
        : root_({range_begin, range_end})
    {}

    void update(int range_begin, int range_end, int delta)
    {
        root_.update({range_begin, range_end}, delta);
    }

    Node query(int range_begin, int range_end)
    {
        return root_.query({range_begin, range_end});
    }

private:
    Segment root_;

}; // class SparseSegmentTree

struct Point {
    int x;
    int y;
};

struct Rectangle {
    Point lb;
    Point ub;
};

struct Event {
    int time;
    int type;
    unsigned index;
};

bool operator <(const Event& lhs, const Event& rhs)
{
    return std::tie(lhs.time, lhs.type, lhs.index) < std::tie(rhs.time, rhs.type, rhs.index);
}

integer solve(const std::vector<Rectangle>& rs)
{
    std::vector<Event> events;
    for (unsigned i = 0; i < rs.size(); ++i) {
        events.push_back({ rs[i].lb.x, 0, i });
        events.push_back({ rs[i].ub.x, 1, i });
    }

    std::sort(events.begin(), events.end());

    integer area = 0;
    {
        SparseSegmentTree st(-1000001, 1000001);

        int t = events[0].time;
        for (const Event& e : events) {
            const Node v = st.query(-1000000, 1000001);
            area += integer(e.time - t) * (v.range_size - v.count);
            st.update(rs[e.index].lb.y, rs[e.index].ub.y, e.type == 0 ? 1 : -1);
            t = e.time;
        }
    }
    return area;
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    unsigned n;
    std::cin >> n;

    std::vector<Rectangle> rs(n);
    for (unsigned i = 0; i < n; ++i)
        std::cin >> rs[i].lb.x >> rs[i].lb.y >> rs[i].ub.x >> rs[i].ub.y;

    std::cout << solve(rs) << '\n';

    return 0;
}
