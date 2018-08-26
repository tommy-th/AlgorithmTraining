struct node {
    int count;
    int idx;
    int value;
    __node(int c, int i, int v)
        : count(c), idx(i), value(v) {}
};

bool operator<(const node& a, const node& b) {
    if (a.count==b.count)
        return a.idx<b.idx;
    return a.count < b.count;
}

class FreqStack {
public:
    FreqStack() = default;

    void push(int x) {
        idx_++;
        auto it = counts_.find(x);
        if (it != counts_.end())
            it->second++;
        else
            counts_.insert(it, {x, 1});

        q_.push({counts_[x], idx_, x});
    }

    int pop() {
        auto c = q_.top();
        q_.pop();

        return c.value;
    }

private:
    int idx_;
    std::priority_queue<node> q_;
    map<int, int> counts_;
};
