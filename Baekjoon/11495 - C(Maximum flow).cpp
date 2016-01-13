//
//  11495 - C(Maximum flow).cpp
//  AlgorithmTraining
//
//  Created by JangTaehwan on 2016. 1. 13..
//  Copyright © 2016년 JangTaehwan. All rights reserved.
//

#include <iostream>
#include <cstring>
#include <vector>
#include <queue>
using namespace std;

#define INF 100000000
#define MAXV 55*55
#define MAXE 55*55*10

int valid(int, int);
const int dir[4][2] = {{0,1}, {0,-1}, {1,0}, {-1,0}};

int N, M, T;
int map[55][55], vmap[55][55];

int aidx, bidx, eidx, vidx;
vector<int> g[MAXE];
int vertexs[MAXE], flows[MAXE];

vector<int> path;
int hmap[MAXE];

void add_edge(int a, int b, int f){
    vertexs[eidx] = b; flows[eidx] = f; g[a].push_back(eidx); eidx++;
    vertexs[eidx] = a; flows[eidx] = 0; g[b].push_back(eidx); eidx++;
}

int dfs(int n){
    hmap[n] = 1;
    if(n==vidx) return 1;
    
    for(int i=0; i<g[n].size(); i++){
        int edge = g[n][i];
        if(flows[edge]) {
            if(hmap[vertexs[edge]]) continue;
             path.push_back(edge);
            if(dfs(vertexs[edge])) return 1;
            else path.pop_back();
        }
    }
    
    return 0;
}

int max_flow(){
    int result = 0;
    
    memset(hmap, 0, sizeof(hmap));
    path.clear();
    while(dfs(0)){
        int min = INF;
        for(int i=0; i<path.size(); i++){
            int edge = path[i];
            if(flows[edge] < min) min = flows[edge];
        }
        for(int i=0; i<path.size(); i++){
            int edge = path[i];
            flows[edge] -= min;
            flows[edge^1] += min;
        }
        result += min;
        path.clear();
        memset(hmap, 0, sizeof(hmap));
    }
    
    return result;
}

int main(){
    int result;
    
    cin>>T;
    for(int t=1; t<=T; t++){
        result = 0;
        
        cin>>N>>M;
        for(int i=1; i<=N; i++){
            for(int j=1; j<=M; j++){
                cin>>map[i][j];
                result += map[i][j];
            }
        }
        
        eidx = aidx = bidx = 0;
        for(int i=1; i<=N; i++){
            for(int j=1; j<=M; j++){
                if((i+j)&1) vmap[i][j] = ++bidx;
                else vmap[i][j] = ++aidx;
            }
        }
        vidx = aidx + bidx +1;
        
        for(int i=0; i<=vidx; i++) g[i].clear();
        for(int i=1; i<=N; i++){
            for(int j=1; j<=M; j++){
                if((i+j)&1) add_edge(aidx + vmap[i][j], vidx, map[i][j]);
                else{
                    add_edge(0, vmap[i][j], map[i][j]);
                    for(int k=0; k<4; k++) {
                        int y = i+dir[k][0], x = j+dir[k][1];
                        if(valid(y, x)) add_edge(vmap[i][j], aidx + vmap[y][x], INF);
                    }
                }
            }
        }
        
        cout<<result - max_flow()<<endl;
    }
    
    return 0;
}

int valid(int y, int x){
    if(y<=0 || y > N || x<=0 || x>M) return 0;
    else return 1;
}




