class Solution {
public:
    int numRescueBoats(vector<int>& people, int limit) {
        int result = 0;
        vector<int> weights(30005, 0);

        for (auto person : people) {
            weights[person]++;
        }

        for (int i = 30000; i >=1; i--) {
            if (weights[i] <= 0) continue;
            int otherMax = limit - i;

            if (otherMax >= i) {
                result += (weights[i] / 2);
                if (weights[i] % 2 == 1)
                    weights[i] = 1;
                else
                    weights[i] = 0;
                otherMax = i - 1;
            }

            for (int j = otherMax; j >= 1; j--) {
                if (weights[i] <= 0) break;
                if (weights[j] <= 0) continue;

                int boats = min(weights[i], weights[j]);
                weights[i] -= boats;
                weights[j] -= boats;
                result += boats;
            }
            result += weights[i];
            weights[i] = 0;
        }
        return result;
    }
};
