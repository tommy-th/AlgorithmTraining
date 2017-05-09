#include <iostream>
#include <vector>
#include <algorithm>

#define OPTN 2005
#define MAXN 100005
#define MAXE 2000005

int n, m;
int sidx = 1;

std::vector<int> edge[MAXN];

int optSize, otherSize;
bool optCheck[OPTN];
std::vector<int> optEdge[OPTN];

int searchNodes(int s){
    int ret = 0;
    
    optCheck[s] = true;
    
    for(int i : optEdge[s]) {
        if(not optCheck[i])
            ret += searchNodes(i);
    }
    
    if (s==0) ret += optSize;
    else ret += 1;
    
    return ret;
}

void checkGroup() {
    std::vector<int> result;
    
    for(int i=0; i<=otherSize; i++){
        if (not optCheck[i])
            result.push_back(searchNodes(i));
    }
    
    std::sort(result.begin(), result.end());
    
    std::cout<< result.size() <<std::endl;
    for(int i=0; i<result.size(); i++)
        std::cout<< result[i] <<" ";
    std::cout<<std::endl;
}

void optimize() {
    std::vector<int> optGroup;
    std::vector<int>& otherGroup = edge[sidx];
    
    int optEdgeCnt[MAXN] = {0,};
    int newIdx[MAXN] = {0,};
    
    otherSize = otherGroup.size();
    optSize = n-otherSize;
    
    int j=0;
    for(int i=1; i<=n; i++) {
        if (otherSize==0) optGroup.push_back(i);
        else if (otherGroup[j] != i) optGroup.push_back(i);
        else if (j < otherSize) j++;
    }
    
    for(int i = 0; i<otherSize; i++) {
        newIdx[otherGroup[i]] = i+1;
    }
    
    for(int i : optGroup) {
        for (int j : edge[i]) {
            optEdgeCnt[j]++;
        }
    }
    
    for(int i : otherGroup) {
        if (optEdgeCnt[i] < optSize) {
            optEdge[newIdx[i]].push_back(0);
            optEdge[0].push_back(newIdx[i]);
        }
    }
    
    for(int i=0; i<otherSize-1; i++) {
        for(int j=i+1; j<otherSize; j++) {
            const std::vector<int>& v = edge[otherGroup[i]];
            
            if (not std::binary_search(v.begin(), v.end(), otherGroup[j])) {
                int a = newIdx[otherGroup[i]];
                int b = newIdx[otherGroup[j]];
                
                optEdge[a].push_back(b);
                optEdge[b].push_back(a);
            }
        }
    }
}

int main() {
    int a, b;
    
    std::cin >> n >> m;
    
    int count[MAXN] = { 0, };
    
    std::vector<std::pair<int, int>> input;
    std::pair<int, int> prev = {0, 0};
    
    for(int i=0; i<m; i++) {
        std::cin >> a >> b;
        if (a == b) continue;
        if (a > b) std::swap(a, b);
        
        input.push_back({a, b});
    }
    
    std::sort(input.begin(), input.end(),
        [](const std::pair<int, int>& lhs, const std::pair<int, int>& rhs){
            return (lhs.first < rhs.first) || (lhs.first==rhs.first && lhs.second < rhs.second);
        });
    
    for(auto s: input){
        if (s == prev) continue;
        
        prev = s;
        
        a = s.first;
        b = s.second;
        
        edge[a].push_back(b);
        edge[b].push_back(a);
        count[a]++;
        count[b]++;
    }
    
    for(int i=1; i<=n; i++) {
        if(count[i]<count[sidx])
            sidx = i;
    }
    
    optimize();
    checkGroup();
    
    return 0;
}