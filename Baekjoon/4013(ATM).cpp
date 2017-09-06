#include <iostream>
#include <stack>
#include <queue>
#include <vector>
#include <algorithm>

int vNum, eNum, stNum, resNum, sccNum;

using EdgeType = std::vector<std::vector<int>>;

EdgeType edges;
std::vector<int> vCash;
std::vector<bool> vRest;

std::vector<int> sccRoot;
EdgeType sccEdges;
std::vector<int> sccCash;
std::vector<bool> sccRest;

std::stack<int> st;
std::vector<int> check;

int dfs(int cur) {
    static int checkCnt = 0;

    int ret = check[cur] = ++checkCnt;
    st.push(cur);

    for (int next : edges[cur]) {
        if (not check[next])
            ret = std::min(ret, dfs(next));
        else if (not sccRoot[next])
            ret = std::min(ret, check[next]);
    }

    if (ret == check[cur]) {
        ++sccNum;

        while (true) {
            int v = st.top(); st.pop();
            sccRoot[v] = sccNum;
            if (cur == v)
                break;
        }
    }
    return ret;
}

void makeScc() {
    dfs(stNum);

    sccEdges = EdgeType(sccNum+1);
    sccCash = std::vector<int>(sccNum+1, 0);
    sccRest = std::vector<bool>(sccNum+1, false);

    for (int cur = 1; cur <= vNum; cur++) {
        int a = sccRoot[cur];

        sccCash[a] += vCash[cur];
        if (vRest[cur])
            sccRest[a] = true;

        for (int next : edges[cur]) {
            int b = sccRoot[next];
            if (a != b)
                sccEdges[a].push_back(b);
        }
    }
}

int calcMaxCash() {
    int result = 0;

    std::queue<int> bfs;
    std::vector<int> dp(sccNum+1, 0);
    std::vector<bool> queued(sccNum+1, false);

    stNum = sccRoot[stNum];
    bfs.push(stNum);
    queued[stNum] = true;

    for (int i = 1; i <= sccNum; i++) 
        dp[i] = sccCash[i];

    while(not bfs.empty()) {
        int cur = bfs.front(); bfs.pop();
        queued[cur] = false;

        for(int next : sccEdges[cur]) {
            if (dp[cur] + sccCash[next] > dp[next]) {
                dp[next] = dp[cur] + sccCash[next];

                if (not queued[next]) {
                    bfs.push(next);
                    queued[next] = true;
                }
            }
        }
    }

    for (int i = 1; i <= sccNum; i++) {
        if (sccRest[i])
            result = std::max(result, dp[i]);
    }

    return result;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin >> vNum >> eNum;

    vCash = std::vector<int>(vNum+1, 0);
    vRest = std::vector<bool>(vNum+1, false);
    edges = EdgeType(vNum+1);
    check = std::vector<int>(vNum+1, 0);

    sccRoot = std::vector<int>(vNum+1, 0);

    for(int i=1; i<=eNum; i++) {
        int a, b;
        std::cin >> a >> b;
        edges[a].push_back(b);
    }

    for(int i=1; i<=vNum; i++) {
        int cash;
        std::cin >> cash;
        vCash[i] = cash;
    }

    std::cin >> stNum >> resNum;

    for(int i=1; i<=resNum; i++) {
        int rest;
        std::cin>>rest;
        vRest[rest] = true;
    }

    makeScc();
    std::cout << calcMaxCash() << std::endl;
}
