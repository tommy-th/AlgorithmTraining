#include <iostream>
#include <iomanip>
#include <memory>
#include <string>
#include <vector>
#include <queue>
#include <unordered_map>

using namespace std;

struct Node;
using DataType = std::string;
using KeyType = DataType::value_type;
using NodePtr = shared_ptr<Node>;
using NodeLinkPtr = weak_ptr<Node>;

struct Node {
    KeyType key = '\0';
    uint64_t dataSize = 0;
    NodeLinkPtr failure;
    NodeLinkPtr output;
    unordered_map<KeyType, NodePtr> nexts;

    Node() = default;
    Node(KeyType k) : key(k) {}

    bool isMatched() {
        return dataSize > 0;
    }

    void insert(KeyType key) {
        const auto got = nexts.find(key);
        if (got == nexts.end()) {
            nexts[key] = make_shared<Node>(key);
        }
    }

    NodePtr find(KeyType key) {
        const auto got = nexts.find(key);

        if (got != nexts.end())
            return (*got).second;
        else
            return nullptr;
    }
};

class AhoCorasick {
public:
    void makeTrie(vector<DataType> patterns) {
        root_ = make_shared<Node>();

        for (const auto& pattern : patterns) {
            NodePtr cur = root_;
            for (uint64_t i = 0; i < pattern.size(); i++) {
                cur->insert(pattern[i]);
                cur = cur->nexts[pattern[i]];
            }
            cur->dataSize = pattern.size();
        }

        queue<pair<NodePtr, NodePtr>> bfs;
        bfs.push({root_, root_});

        while (not bfs.empty()) {
            NodePtr prev = bfs.front().first;
            NodePtr cur = bfs.front().second;
            bfs.pop();

            makeFailureAndOutput(prev, cur);

            for (const auto& next : cur->nexts) {
                bfs.push({cur, next.second});
            }
        }
    }

    vector<pair<uint64_t, uint64_t>> search(const DataType& source) {
        vector<pair<uint64_t, uint64_t>> ret;
        NodePtr cur = root_;

        for (uint64_t i=0; i < source.size(); i++) {
            NodePtr next = cur->find(source[i]);
            if (not next) {
                do {
                    cur = cur->failure.lock();
                    next = cur->find(source[i]);
                    if (next) break;
                } while (cur != root_);
            }

            if (next) {
                cur = next;
                while (next) {
                    if (next->isMatched())
                        ret.push_back({i - next->dataSize + 1, next->dataSize});
                    next = next->output.lock();
                }
            }
        }

        return ret;
    }

protected:
    void makeFailureAndOutput(NodePtr cur, NodePtr next) {
        while (cur != root_) {
            NodePtr failure = cur->failure.lock();
            next->failure = failure->find(next->key);

            if (not next->failure.expired()) {
                break;
            } else {
                cur = failure;
            }
        }
        if (cur == root_) {
            next->failure = root_;
        }

        if (next->failure.lock()->isMatched()) {
            next->output = next->failure;
        } else {
            next->output = next->failure.lock()->output;
        }
    }

private: 
    NodePtr root_;
};


int main() {
    vector<DataType> testPatterns = {"a", "ab", "bab", "bc", "bca", "c", "caa"};

    AhoCorasick ac;
    ac.makeTrie(testPatterns);
    auto result = ac.search("abccab");

    for (auto indexs : result) {
        cout << indexs.first << " " << indexs.second << endl;
    }
}
