#include "leetcode.h"

class RLEIterator {
public:
    RLEIterator(vector<int> A) {
        list_ = A;
    }

    int next(int n) {
        while (idx_<list_.size()) {
            if (list_[idx_] >= n) {
                list_[idx_] -= n;
                return list_[idx_+1];
            } else {
                n -= list_[idx_];
                list_[idx_] = 0;
                idx_ += 2;
            }
        }
        return -1;
    }

private:
    int idx_ = 0;
    vector<int> list_;
};