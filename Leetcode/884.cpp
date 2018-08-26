class Solution {
public:
    template<typename Out>
    void split(const std::string &s, char delim, Out result) {
        std::stringstream ss(s);
        std::string item;
        while (std::getline(ss, item, delim)) {
            *(result++) = item;
        }
    }

    std::vector<std::string> split(const std::string &s, char delim) {
        std::vector<std::string> elems;
        split(s, delim, std::back_inserter(elems));
        return elems;
    }

    vector<string> uncommonFromSentences(string A, string B) {
        vector<string> ret;
        std::vector<std::string> asplit = split(A, ' ');
        std::vector<std::string> bsplit = split(B, ' ');

        for (int i = 0; i< asplit.size(); i++) {
            bool valid = true;
            for (int j = 0; j< asplit.size(); j++) {
                if (i != j) {
                    if (asplit[i] == asplit[j]) {
                        valid = false;
                        break;
                    }
                }
            }
            if (not valid) continue;
            for (int j = 0; j< bsplit.size(); j++) {
                if (asplit[i] == bsplit[j]) {
                    valid = false;
                    break;
                }
            }
            if (valid) ret.push_back(asplit[i]);
        }

        for (int i = 0; i< bsplit.size(); i++) {
            bool valid = true;
            for (int j = 0; j< bsplit.size(); j++) {
                if (i != j) {
                    if (bsplit[i] == bsplit[j]) {
                        valid = false;
                        break;
                    }
                }
            }
            if (not valid) continue;
            for (int j = 0; j< asplit.size(); j++) {
                if (bsplit[i] == asplit[j]) {
                    valid = false;
                    break;
                }
            }
            if (valid) ret.push_back(bsplit[i]);
        }

        return ret;
    }
};
