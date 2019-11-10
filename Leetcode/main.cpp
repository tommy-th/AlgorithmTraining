#include "1255.h"

int main() {
    Solution s = Solution();
    vector<string> words = {"dog","cat","dad","good"};
    vector<char> letters = { 'a','a', 'c','d','d','d','g','o','o'};
    vector<int> scores = {1,0,9,5,0,0,3,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0};

    cout << s.maxScoreWords(words, letters, scores) << endl;
}
