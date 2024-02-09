#include <iostream>
#include <optional>
#include <vector>

template <typename Node, typename Update>
class SegmentTree {
public:
    explicit SegmentTree(unsigned size)
        : size_(1 << w - __builtin_clz(size) + 1)
        , nodes_(2 * size_)
        , updates_(2 * size_)
    {
        for (unsigned i = size_ - 1; i > 0; --i)
            nodes_[i] = Node(nodes_[i * 2], nodes_[i * 2 + 1]);
    }

    template <typename Iterator>
    SegmentTree(Iterator begin, Iterator end)
        : size_(1 << w - __builtin_clz(end - begin) + 1)
        , nodes_(2 * size_)
        , updates_(2 * size_)
    {
        unsigned i = size_;
        for (auto it = begin; it != end; ++it)
            nodes_[i++] = Node(*it);

        for (unsigned i = size_ - 1; i > 0; --i)
            nodes_[i] = Node(nodes_[i * 2], nodes_[i * 2 + 1]);
    }

    template <typename... Ts>
    void update_point(unsigned index, Ts&&... arguments)
    {
        update_point({1, 0, size_}, index, std::forward<Ts>(arguments)...);
    }

    template <typename... Ts>
    void update_range(unsigned range_begin, unsigned range_end, Ts&&... arguments)
    {
        update_range({1, 0, size_}, range_begin, range_end, std::forward<Ts>(arguments)...);
    }

    std::optional<Node> query_point(unsigned index)
    {
        return query_point({1, 0, size_}, index);
    }

    std::optional<Node> query_range(unsigned range_begin, unsigned range_end)
    {
        return query_range({1, 0, size_}, range_begin, range_end);
    }

    template <typename F>
    std::optional<unsigned> search(F&& predicate)
    {
        return predicate(0, size_, nodes_[1]) ? search({1, 0, size_}, predicate) : std::nullopt;
    }

private:
    struct Segment {
        unsigned index;
        unsigned range_begin;
        unsigned range_end;

        std::pair<Segment, Segment> split() const
        {
            const unsigned mid_point = (range_begin + range_end) / 2;
            return {{ index * 2, range_begin, mid_point }, { index * 2 + 1, mid_point, range_end }};
        }
    };

    static const Segment& select_segment(const std::pair<Segment, Segment>& segments, unsigned point)
    {
        return point < segments.first.range_end ? segments.first : segments.second;
    }

    template <typename... Ts>
    void update_point(const Segment& segment, unsigned index, Ts&&... arguments)
    {
        if (segment.range_begin + 1 == segment.range_end) {
            aggregate_updates(segment.index, Update(std::forward<Ts>(arguments)...));
            return;
        }

        propagate_updates(segment.index);

        const std::pair<Segment, Segment> subsegments = segment.split();
        update_point(select_segment(subsegments, index), index, std::forward<Ts>(arguments)...);
        nodes_[segment.index] = Node(nodes_[subsegments.first.index], nodes_[subsegments.second.index]);
    }

    template <typename... Ts>
    void update_range(const Segment& segment, unsigned range_begin, unsigned range_end, Ts&&... arguments)
    {
        if (range_end <= segment.range_begin || segment.range_end <= range_begin)
            return;

        if (range_begin <= segment.range_begin && segment.range_end <= range_end) {
            aggregate_updates(segment.index, Update(std::forward<Ts>(arguments)...));
            return;
        }

        propagate_updates(segment.index);

        const std::pair<Segment, Segment> subsegments = segment.split();
        update_range(subsegments.first, range_begin, range_end, std::forward<Ts>(arguments)...);
        update_range(subsegments.second, range_begin, range_end, std::forward<Ts>(arguments)...);
        nodes_[segment.index] = Node(nodes_[subsegments.first.index], nodes_[subsegments.second.index]);
    }

    std::optional<Node> query_point(const Segment& segment, unsigned index)
    {
        if (segment.range_begin + 1 == segment.range_end)
            return nodes_[segment.index];

        propagate_updates(segment.index);

        const std::pair<Segment, Segment> subsegments = segment.split();
        return query_point(select_segment(subsegments, index), index);
    }

    std::optional<Node> query_range(const Segment& segment, unsigned range_begin, unsigned range_end)
    {
        if (range_end <= segment.range_begin || segment.range_end <= range_begin)
            return std::nullopt;

        if (range_begin <= segment.range_begin && segment.range_end <= range_end)
            return nodes_[segment.index];

        propagate_updates(segment.index);

        const std::pair<Segment, Segment> subsegments = segment.split();
        const std::optional<Node> lhs = query_range(subsegments.first, range_begin, range_end);
        const std::optional<Node> rhs = query_range(subsegments.second, range_begin, range_end);
        if (lhs && rhs)
            return Node(*lhs, *rhs);

        return lhs ? lhs : rhs;
    }

    template <typename F>
    std::optional<unsigned> search(const Segment& segment, F&& predicate)
    {
        if (segment.range_begin + 1 == segment.range_end)
            return segment.range_begin;

        propagate_updates(segment.index);

        std::optional<unsigned> location;

        const std::pair<Segment, Segment> subsegments = segment.split();
        if (!location && predicate(subsegments.first.range_begin, subsegments.first.range_end, nodes_[subsegments.first.index]))
            location = search(subsegments.first, predicate);
        if (!location && predicate(subsegments.second.range_begin, subsegments.second.range_end, nodes_[subsegments.second.index]))
            location = search(subsegments.second, predicate);

        return location;
    }

    void aggregate_updates(unsigned index, const Update& update)
    {
        if (!updates_[index])
            updates_[index] = update;
        else
            updates_[index]->aggregate(update);

        update.apply(nodes_[index]);
    }

    void propagate_updates(unsigned index)
    {
        if (updates_[index]) {
            aggregate_updates(index * 2, *updates_[index]);
            aggregate_updates(index * 2 + 1, *updates_[index]);

            updates_[index] = std::nullopt;
        }
    }

private:
    const unsigned size_;

    std::vector<Node> nodes_;
    std::vector<std::optional<Update>> updates_;

    static constexpr unsigned w = __builtin_clz(1);

}; // class SegmentTree<Node, Update>

using integer = unsigned long long;

struct Node {
    unsigned range_size = 1;
    integer sum = 0;

    Node() = default;

    explicit Node(unsigned value)
        : sum(value)
    {}

    Node(const Node& lhs, const Node& rhs)
        : range_size(lhs.range_size + rhs.range_size)
        , sum(lhs.sum + rhs.sum)
    {}

    void update(unsigned type, integer value)
    {
        if (type == 1) {
            sum += value * range_size;
        } else {
            sum = value * range_size;
        }
    }
};

struct Update {
    unsigned type;
    integer value;

    Update(unsigned type, unsigned value)
        : type(type)
        , value(value)
    {}

    void aggregate(const Update& update)
    {
        if (update.type == 1) {
            value += update.value;
        } else {
            type = 2;
            value = update.value;
        }
    }

    void apply(Node& target_node) const
    {
        target_node.update(type, value);
    }
};

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    unsigned n, q;
    std::cin >> n >> q;

    std::vector<unsigned> ts(n);
    for (unsigned i = 0; i < n; ++i)
        std::cin >> ts[i];

    SegmentTree<Node, Update> st(ts.begin(), ts.end());
    for (unsigned i = 0; i < q; ++i) {
        unsigned t;
        std::cin >> t;

        if (t == 3) {
            unsigned a, b;
            std::cin >> a >> b;

            std::cout << st.query_range(a-1, b)->sum << '\n';
        } else {
            unsigned a, b, x;
            std::cin >> a >> b >> x;

            st.update_range(a-1, b, t, x);
        }
    }

    return 0;
}
