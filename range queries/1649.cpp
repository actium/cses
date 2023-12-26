#include <iostream>
#include <vector>

class SegmentTree {
    struct Node {
        unsigned min = ~0u;

        void initialize(unsigned value)
        {
            min = value;
        }

        static Node compose(const Node& lhs, const Node& rhs)
        {
            return {
                .min = std::min(lhs.min, rhs.min),
            };
        }
    };

public:
    explicit SegmentTree(unsigned size)
        : size_(1 << __builtin_clz(1) - __builtin_clz(size) + 1)
        , nodes_(2 * size_)
    {}

    template <typename Iterator>
    SegmentTree(Iterator begin, Iterator end)
        : SegmentTree(std::distance(begin, end))
    {
        unsigned i = size_;
        for (auto it = begin; it != end; ++it)
            nodes_[i++].initialize(*it);

        for (unsigned i = size_ - 1; i > 0; --i)
            nodes_[i] = Node::compose(nodes_[i<<1|0], nodes_[i<<1|1]);
    }

    void set(unsigned index, unsigned value)
    {
        set({ 1, 0, size_ }, index, value);
    }

    Node query(unsigned range_begin, unsigned range_end)
    {
        return query({ 1, 0, size_ }, range_begin, range_end);
    }

private:
    struct Subtree {
        unsigned root_index;
        unsigned range_begin;
        unsigned range_end;
    };

    void set(const Subtree& subtree, unsigned index, unsigned value)
    {
        if (subtree.range_begin + 1 == subtree.range_end) {
            nodes_[subtree.root_index].initialize(value);
            return;
        }

        const unsigned mid = (subtree.range_begin + subtree.range_end) / 2;
        if (index < mid) {
            set({ subtree.root_index<<1|0, subtree.range_begin, mid }, index, value);
        } else {
            set({ subtree.root_index<<1|1, mid, subtree.range_end }, index, value);
        }

        nodes_[subtree.root_index] = Node::compose(nodes_[subtree.root_index<<1|0], nodes_[subtree.root_index<<1|1]);
    }

    Node query(const Subtree& subtree, unsigned range_begin, unsigned range_end)
    {
        if (range_end <= subtree.range_begin || subtree.range_end <= range_begin)
            return {};

        if (range_begin <= subtree.range_begin && subtree.range_end <= range_end)
            return nodes_[subtree.root_index];

        const unsigned mid = (subtree.range_begin + subtree.range_end) / 2;
        return Node::compose(
            query({ subtree.root_index<<1|0, subtree.range_begin, mid }, range_begin, range_end),
            query({ subtree.root_index<<1|1, mid, subtree.range_end }, range_begin, range_end)
        );
    }

private:
    const unsigned size_;

    std::vector<Node> nodes_;

}; // class SegmentTree

int main()
{
    unsigned n, q;
    std::cin >> n >> q;

    std::vector<unsigned> xs(n);
    for (unsigned i = 0; i < n; ++i)
        std::cin >> xs[i];

    SegmentTree st(xs.begin(), xs.end());
    for (unsigned i = 0; i < q; ++i) {
        unsigned t;
        std::cin >> t;

        if (t == 1) {
            unsigned k, u;
            std::cin >> k >> u;

            st.set(k-1, u);
        } else {
            unsigned a, b;
            std::cin >> a >> b;

            std::cout << st.query(a-1, b).min << '\n';
        }
    }

    return 0;
}
