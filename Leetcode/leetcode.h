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


#endif //ALGORITHMTRAINING_LEETCODE_H
