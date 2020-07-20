#ifndef ALGORITHMTRAINING_LEETCODE_H
#define ALGORITHMTRAINING_LEETCODE_H

#include <vector>
#include <string>
#include <stack>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <algorithm>
#include <iostream>
#include <numeric>
#include <cmath>
#include <queue>
#include <sstream>

using namespace std;


vector<string> splitString(string str, char delimiter) {
    vector<string> internal;
    stringstream ss(str);
    string temp;

    while (getline(ss, temp, delimiter)) {
        if (not temp.empty()) {
            internal.push_back(temp);
        }
    }

    return internal;
}


class FenwickTree {
 public:
    FenwickTree(int max_size)
        : n(max_size)
        , counts(n + 1, 0) {
    }

    void update(int idx, int diff) {
        do {
            counts[idx] += diff;
            idx += idx & -idx;
        } while(idx <= n);
    }

    int sums(int idx) {
        int ret = 0;

        do {
            ret += counts[idx];
            idx -= idx & -idx;
        } while(idx > 0);

        return ret;
    }

 private:
   int n;
   vector<int> counts;
};


#endif //ALGORITHMTRAINING_LEETCODE_H
