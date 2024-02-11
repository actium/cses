#include <iostream>
#include <optional>
#include <vector>

template <typename Value, typename Operation>
class SegmentTree {
public:
    explicit SegmentTree(unsigned size)
        : size_(1 << (w - __builtin_clz(size) + 1))
        , values_(2 * size_)
        , operations_(2 * size_)
    {
        for (unsigned i = size_ - 1; i > 0; --i)
            recompute_value(i);
    }

    template <typename Iterator>
    SegmentTree(Iterator begin, Iterator end)
        : size_(1 << (w - __builtin_clz(end - begin) + 1))
        , values_(2 * size_)
        , operations_(2 * size_)
    {
        unsigned i = size_;
        for (auto it = begin; it != end; ++it)
            values_[i++] = Value(*it);

        for (unsigned i = size_ - 1; i > 0; --i)
            recompute_value(i);
    }

    void update(unsigned point, const Operation& operation)
    {
        update({1, 0, size_}, point, operation);
    }

    void update(unsigned range_begin, unsigned range_end, const Operation& operation)
    {
        update({1, 0, size_}, range_begin, range_end, operation);
    }

    Value query(unsigned point)
    {
        return query({1, 0, size_}, point);
    }

    Value query(unsigned range_begin, unsigned range_end)
    {
        return query({1, 0, size_}, range_begin, range_end);
    }

    template <typename Predicate>
    std::optional<unsigned> search(Predicate&& predicate)
    {
        return predicate(0, size_, values_[1]) ? search({1, 0, size_}, std::forward<Predicate>(predicate)) : std::nullopt;
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

    void update(const Segment& segment, unsigned point, const Operation& operation)
    {
        if (segment.range_begin + 1 == segment.range_end) {
            aggregate_operation(segment.index, operation);
        } else {
            propagate_operation(segment.index);

            const std::pair<Segment, Segment> subsegments = segment.split();
            update(select_segment(subsegments, point), point, operation);
            recompute_value(segment.index);
        }
    }

    void update(const Segment& segment, unsigned range_begin, unsigned range_end, const Operation& operation)
    {
        if (range_end <= segment.range_begin || segment.range_end <= range_begin)
            return;

        if (range_begin <= segment.range_begin && segment.range_end <= range_end) {
            aggregate_operation(segment.index, operation.shift(segment.range_begin - range_begin));
        } else {
            propagate_operation(segment.index);

            const std::pair<Segment, Segment> subsegments = segment.split();
            update(subsegments.first, range_begin, range_end, operation);
            update(subsegments.second, range_begin, range_end, operation);
            recompute_value(segment.index);
        }
    }

    Value query(const Segment& segment, unsigned point)
    {
        if (point < segment.range_begin || point >= segment.range_end)
            return Value();

        if (segment.range_begin + 1 == segment.range_end)
            return values_[segment.index];

        propagate_operation(segment.index);

        const std::pair<Segment, Segment> subsegments = segment.split();
        return query(select_segment(subsegments, point), point);
    }

    Value query(const Segment& segment, unsigned range_begin, unsigned range_end)
    {
        if (range_end <= segment.range_begin || segment.range_end <= range_begin)
            return Value();

        if (range_begin <= segment.range_begin && segment.range_end <= range_end)
            return values_[segment.index];

        propagate_operation(segment.index);

        const std::pair<Segment, Segment> subsegments = segment.split();
        return Value(query(subsegments.first, range_begin, range_end), query(subsegments.second, range_begin, range_end));
    }

    void aggregate_operation(unsigned index, const Operation& operation)
    {
        if (!operations_[index])
            operations_[index] = operation;
        else
            operations_[index]->aggregate(operation);

        operation.apply(values_[index]);
    }

    void propagate_operation(unsigned index)
    {
        if (operations_[index]) {
            aggregate_operation(index * 2, *operations_[index]);
            aggregate_operation(index * 2 + 1, *operations_[index]);

            operations_[index] = std::nullopt;
        }
    }

    void recompute_value(unsigned index)
    {
        values_[index] = Value(values_[index * 2], values_[index * 2 + 1]);
    }

    template <typename Predicate>
    std::optional<unsigned> search(const Segment& segment, Predicate&& predicate)
    {
        if (segment.range_begin + 1 == segment.range_end)
            return segment.range_begin;

        propagate_operation(segment.index);

        std::optional<unsigned> location;

        const std::pair<Segment, Segment> subsegments = segment.split();
        if (!location && predicate(subsegments.first.range_begin, subsegments.first.range_end, values_[subsegments.first.index]))
            location = search(subsegments.first, std::forward<Predicate>(predicate));
        if (!location && predicate(subsegments.second.range_begin, subsegments.second.range_end, values_[subsegments.second.index]))
            location = search(subsegments.second, std::forward<Predicate>(predicate));

        return location;
    }

private:
    const unsigned size_;

    std::vector<Value> values_;
    std::vector<std::optional<Operation>> operations_;

    static constexpr unsigned w = __builtin_clz(1);

}; // class SegmentTree<Value, Operation>

using integer = long long;

struct Value {
    unsigned range_size = 1;

    integer sum = 0;

    Value() = default;

    explicit Value(integer sum)
        : sum(sum)
    {}

    Value(const Value& lhs, const Value& rhs)
        : range_size(lhs.range_size + rhs.range_size)
        , sum(lhs.sum + rhs.sum)
    {}
};

struct Operation {
    mutable integer base;
    integer delta;

    Operation(integer base, integer delta)
        : base(base)
        , delta(delta)
    {}

    Operation shift(unsigned offset) const
    {
        return Operation(base + offset, delta);
    }

    void aggregate(const Operation& operation)
    {
        base += operation.base;
        delta += operation.delta;
    }

    void apply(Value& target) const
    {
        target.sum += base * target.range_size + delta * target.range_size * (target.range_size - 1) / 2;
        base += delta * target.range_size;
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

    SegmentTree<Value, Operation> st(ts.begin(), ts.end());
    for (unsigned i = 0; i < q; ++i) {
        unsigned t, a, b;
        std::cin >> t >> a >> b;

        if (t == 1) {
            st.update(a-1, b, Operation(1, 1));
        } else {
            std::cout << st.query(a-1, b).sum << '\n';
        }
    }

    return 0;
}
