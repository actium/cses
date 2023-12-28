#include <iostream>
#include <vector>

class SegmentTree {
    struct Node {
        unsigned range_size = 1;
        unsigned long long sum = 0;
        unsigned long long common_delta = 0;

        void initialize(unsigned value)
        {
            sum = value;
        }

        void update(unsigned long long delta)
        {
            sum += range_size * delta;
            common_delta += delta;
        }

        void propagate_updates(Node& lhs, Node& rhs)
        {
            if (common_delta != 0) {
                lhs.update(common_delta);
                rhs.update(common_delta);
                common_delta = 0;
            }
        }

        static Node compose(const Node& lhs, const Node& rhs)
        {
            return {
                .range_size = lhs.range_size + rhs.range_size,
                .sum = lhs.sum + rhs.sum,
            };
        }
    };

public:
    template <typename Iterator>
    SegmentTree(Iterator begin, Iterator end)
    {
        const unsigned n = std::distance(begin, end);

        size_ = 1 << __builtin_clz(1) - __builtin_clz(n) + 1;
        nodes_.resize(2 * size_);

        unsigned i = size_;
        for (auto it = begin; it != end; ++it)
            nodes_[i++].initialize(*it);

        for (unsigned i = size_ - 1; i > 0; --i)
            nodes_[i] = Node::compose(nodes_[i<<1|0], nodes_[i<<1|1]);
    }

    template <typename... T>
    void update(unsigned range_begin, unsigned range_end, T&&... arguments)
    {
        update({ 1, 0, size_ }, range_begin, range_end, std::forward<T>(arguments)...);
    }

    Node query(unsigned range_begin, unsigned range_end)
    {
        return query(range_begin, range_end, { 1, 0, size_ });
    }

private:
    struct Subtree {
        unsigned root_index;
        unsigned range_begin;
        unsigned range_end;
    };

    template <typename... T>
    void update(const Subtree& subtree, unsigned range_begin, unsigned range_end, T&&... arguments)
    {
        if (range_end <= subtree.range_begin || subtree.range_end <= range_begin)
            return;

        if (range_begin <= subtree.range_begin && subtree.range_end <= range_end) {
            nodes_[subtree.root_index].update(std::forward<T>(arguments)...);
            return;
        }

        nodes_[subtree.root_index].propagate_updates(nodes_[subtree.root_index<<1|0], nodes_[subtree.root_index<<1|1]);

        const unsigned mid = (subtree.range_begin + subtree.range_end) / 2;
        update({ subtree.root_index<<1|0, subtree.range_begin, mid }, range_begin, range_end, std::forward<T>(arguments)...);
        update({ subtree.root_index<<1|1, mid, subtree.range_end }, range_begin, range_end, std::forward<T>(arguments)...);
        nodes_[subtree.root_index] = Node::compose(nodes_[subtree.root_index<<1|0], nodes_[subtree.root_index<<1|1]);
    }

    Node query(unsigned range_begin, unsigned range_end, const Subtree& subtree)
    {
        if (range_end <= subtree.range_begin || subtree.range_end <= range_begin)
            return {};

        if (range_begin <= subtree.range_begin && subtree.range_end <= range_end)
            return nodes_[subtree.root_index];

        nodes_[subtree.root_index].propagate_updates(nodes_[subtree.root_index<<1|0], nodes_[subtree.root_index<<1|1]);

        const unsigned mid = (subtree.range_begin + subtree.range_end) / 2;
        return Node::compose(
            query(range_begin, range_end, { subtree.root_index<<1|0, subtree.range_begin, mid }),
            query(range_begin, range_end, { subtree.root_index<<1|1, mid, subtree.range_end })
        );
    }

private:
    unsigned size_;

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
            unsigned a, b, u;
            std::cin >> a >> b >> u;

            st.update(a-1, b, u);
        } else {
            unsigned k;
            std::cin >> k;

            std::cout << st.query(k-1, k).sum << '\n';
        }
    }

    return 0;
}
