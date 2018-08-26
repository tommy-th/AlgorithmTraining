class Solution {
public:
    vector<string> findAndReplacePattern(vector<string>& words, string pattern) {
        vector<string> ret;

        for (const auto& word : words) {
            bool valid = true;
            unordered_map<char, char> ptow;
            unordered_map<char, char> wtop;

            for (int i=0; i<pattern.size(); i++) {
                if (ptow[pattern[i]] == '\0' && wtop[word[i]] == '\0') {
                    ptow[pattern[i]] = word[i];
                    wtop[word[i]] = pattern[i];
                } else {
                    if (ptow[pattern[i]] != word[i] && wtop[word[i]] != pattern[i]) {
                        valid = false;
                        break;
                    }
                }
            }
            if (valid)
                ret.push_back(word);
        }
        return ret;
    }
};
