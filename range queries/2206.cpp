#include <iostream>
#include <optional>
#include <vector>

template <typename Value, typename Operation>
class SegmentTree {
public:
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

    Value query(unsigned range_begin, unsigned range_end)
    {
        return query({1, 0, size_}, range_begin, range_end);
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

private:
    const unsigned size_;

    std::vector<Value> values_;
    std::vector<std::optional<Operation>> operations_;

    static constexpr unsigned w = __builtin_clz(1);

}; // class SegmentTree<Value, Operation>

constexpr unsigned oo = ~0u >> 1;

struct Value {
    unsigned range_size = 0;

    unsigned l_min = oo;
    unsigned r_min = oo;

    Value() = default;

    explicit Value(unsigned value)
        : range_size(1)
        , l_min(value)
        , r_min(value)
    {}

    Value(const Value& lhs, const Value& rhs)
        : range_size(lhs.range_size + rhs.range_size)
        , l_min(std::min(lhs.l_min, rhs.l_min + lhs.range_size))
        , r_min(std::min(rhs.r_min, lhs.r_min + rhs.range_size))
    {}
};

struct Operation {
    unsigned value;

    explicit Operation(unsigned value)
        : value(value)
    {}

    void aggregate(const Operation& operation)
    {
        value = operation.value;
    }

    void apply(Value& target) const
    {
        target.l_min = value;
        target.r_min = value;
    }
};

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    unsigned n, q;
    std::cin >> n >> q;

    std::vector<unsigned> ps(n);
    for (unsigned i = 0; i < n; ++i)
        std::cin >> ps[i];

    SegmentTree<Value, Operation> st(ps.begin(), ps.end());
    for (unsigned i = 0; i < q; ++i) {
        unsigned t;
        std::cin >> t;

        if (t == 1) {
            unsigned k, x;
            std::cin >> k >> x;

            st.update(k-1, Operation(x));
        } else {
            unsigned k;
            std::cin >> k;

            std::cout << std::min(st.query(0, k).r_min, st.query(k-1, n).l_min) << '\n';
        }
    }

    return 0;
}
