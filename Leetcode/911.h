#include "leetcode.h"

class TopVotedCandidate {
public:
    TopVotedCandidate(vector<int> persons, vector<int> times) {
        vector<int> votes = vector<int>(persons.size()+1, 0);
        vector<int> counts = vector<int>(persons.size()+1, 0);
        priority_queue<int> pq;

        for (int i=0; i < persons.size(); i++) {
            int person = persons[i];
            votes[person]++;
            counts[votes[person]] = person;
            pq.push(votes[person]);

            int c = pq.top();
            infos_[times[i]] =  counts[c];
        }
    }

    int q(int t) {
        return (--infos_.upper_bound(t))->second;;
    }

private:
    map<int, int> infos_;
};