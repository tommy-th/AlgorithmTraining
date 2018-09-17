#include "leetcode.h"

class Solution {
public:
    int totalFruit(vector<int>& tree) {
        int ret = 0;

        int temp = 0;
        int first = -1;
        int second = -1;

        int count = 0;
        int prev = -1;

        for (int type: tree) {
            if (type != first && type != second) {
                temp = count + 1;

                if (first == prev)
                    second = type;
                else
                    first = type;
                ret = max(temp, ret);
            } else {
                temp++;
                ret = max(temp, ret);
            }

            if (prev != type) {
                prev = type;
                count = 1;
            } else {
                count++;
            }
        }

        return ret;
    }
};