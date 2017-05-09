//
//  2150(Strongly Connected Component).cpp
//  AlgorithmTraining
//
//  Created by Jang on 2017. 5. 7..
//  Copyright © 2017년 JangTaehwan. All rights reserved.
//

#include <iostream>
#include <stack>
#include <queue>
#include <vector>
#include <algorithm>

#define MAXV 10005
#define MAXE 100005

int vNum;
int eNum;

std::queue<int> edges[MAXV];
std::queue<int> redges[MAXV];

std::stack<int> sccOrder;
std::vector<std::vector<int>> sccs;


void makeSccOrder(){
    std::stack<int> dfs;
    int check[MAXV] = {0, };
    
    for(int i=1; i<=vNum; i++){
        if (not check[i]) dfs.push(i);
        
        while(not dfs.empty()) {
            int cur = dfs.top();
            check[cur] = 1;
            
            if(not edges[cur].empty()) {
                int next = edges[cur].front(); edges[cur].pop();
                
                if (not check[next])
                    dfs.push(next);
            } else {
                sccOrder.push(cur);
                dfs.pop();
            }
        }
    }
}

void makeSccGroup(){
    std::stack<int> dfs;
    int check[MAXV] = {0, };
    
    while(not sccOrder.empty()){
        int cur = sccOrder.top(); sccOrder.pop();
        
        if (not check[cur]) dfs.push(cur);
        
        std::vector<int> scc;
        
        while(not dfs.empty()) {
            int cur = dfs.top();
            check[cur] = 1;
            
            if(not redges[cur].empty()) {
                int next = redges[cur].front(); redges[cur].pop();
                
                if (not check[next])
                    dfs.push(next);
            } else {
                scc.push_back(cur);
                dfs.pop();
            }
        }
        
        if (not scc.empty()) sccs.push_back(scc);
    }
}

int main(){
    
    std::cin >> vNum >> eNum;
    
    for(int i=0; i<eNum; i++) {
        int a, b;
        std::cin >> a >> b;
        edges[a].push(b);
        redges[b].push(a);
    }
    
    makeSccOrder();
    makeSccGroup();
    
    for(int i=0; i<sccs.size(); i++)
        std::sort(sccs[i].begin(), sccs[i].end());
    
    std::sort(sccs.begin(), sccs.end(), [](const std::vector<int>& a, const std::vector<int>& b){
        return a[0] < b[0];
    });
    
    std::cout<<sccs.size()<<std::endl;
    
    for(int i=0; i<sccs.size(); i++){
        for(int j=0; j<sccs[i].size(); j++)
            std::cout<<sccs[i][j]<<" ";
        std::cout << -1 << std::endl;
    }
    
    return 0;
}
