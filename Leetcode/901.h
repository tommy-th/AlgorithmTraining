#include "leetcode.h"

class StockSpanner {
public:
    StockSpanner() {
    }

    int next(int price) {
        int ret = 0;
        while (not st.empty()) {
            auto v = st.top();
            if (v.first <= price) {
                ret += v.second;
                st.pop();
            } else break;
        }
        st.push({price, ret + 1});
        return ret + 1;
    }

private:
    int idx=0;
    stack<pair<int, int>> st;
};