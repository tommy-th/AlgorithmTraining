class Solution {
public:
    vector<vector<int>> edges;
    vector<int> roots;

    bool dfs(int root, int cur) {
        if (roots[cur] == root)
            return true;
        else if (roots[cur] == 0)
            roots[cur] = root;
        else
            return false;

        for (auto disNum : edges[cur]) {
            if (roots[disNum] == root) return false;

            for (auto likeNum : edges[disNum]) {
                if (not dfs(root, likeNum)) return false;
            }
        }

        return true;
    }

    bool possibleBipartition(int N, vector<vector<int>>& dislikes) {
        edges = vector<vector<int>>(N+1, vector<int>());

        for (auto dislike : dislikes) {
            edges[dislike[0]].push_back(dislike[1]);
            edges[dislike[1]].push_back(dislike[0]);
        }

        roots = vector<int>(N+1, 0);

        for (int i=1; i<=N; i++) {
            if (roots[i]==0) {
                if (not dfs(i, i))
                    return false;
            }
        }

        return true;
    }
};
