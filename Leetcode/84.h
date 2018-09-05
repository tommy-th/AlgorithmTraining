#include "leetcode.h"

class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        int maxArea = 0;
        stack<int> s;

        heights.push_back(0);
        int maxheight = 0;
        for(int i=0; i<heights.size(); i++) {
            if (maxheight <= heights[i]) {
                maxheight = heights[i];
            } else {
                while (not s.empty() && heights[s.top()] > heights[i]) {
                    int si = s.top(); s.pop();
                    maxArea = max(maxArea, heights[si] * (s.empty() ? i : (i-s.top()-1)));
                }
            }
            s.push(i);
        }

        return maxArea;
    }
};
