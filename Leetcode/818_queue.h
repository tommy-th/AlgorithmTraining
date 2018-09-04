#include "leetcode.h"

class Solution {
public:
    constexpr static int maxNum = 12000;

    int racecar(int target) {
        int ret = 1000000;
        vector<vector<int>> dp = vector<vector<int>>(maxNum + 5, vector<int>(2, 100000));
        vector<vector<bool>> inque = vector<vector<bool>>(maxNum + 5, vector<bool>(2, false));

        dp[0][0] = 0;
        queue<pair<int, int>> q;
        q.push({0, 0});
        inque[0][0] = true;

        while (not q.empty()) {
            auto el = q.front(); q.pop();
            inque[el.first][el.second] = false;

            int cur = el.first;
            int speed = el.second == 0 ? 1 : -1;
            int opt = el.second == 0 ? 1 : 0;
            int count = dp[cur][el.second];

            if (count >= ret)
                continue;

            int next = cur + speed;
            while (next < maxNum && next > 0) {
                count++;
                if (next == target)
                    ret = min(ret, count);

                if (count + 1 < dp[next][opt]) {
                    dp[next][opt] = count + 1;

                    if (not inque[next][opt]) {
                        inque[next][opt] = true;
                        q.push({next, opt});
                    }
                }

                if (count + 2 < dp[next][el.second]) {
                    dp[next][el.second] = count + 2;

                    if (not inque[next][el.second]) {
                        inque[next][el.second] = true;
                        q.push({next, el.second});
                    }
                }

                speed *= 2;
                next += speed;
            }
        }

        return ret;
    }
};
