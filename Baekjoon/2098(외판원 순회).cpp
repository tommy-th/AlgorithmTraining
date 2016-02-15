//
//  2098(외판원 순회).cpp
//  AlgorithmTraining
//
//  Created by JangTaehwan on 2016. 2. 15..
//  Copyright © 2016년 JangTaehwan. All rights reserved.
//

#include <iostream>
#include <queue>
using namespace std;

#define MAXN 20
#define MAXL 65540

int D[MAXN][MAXL];
int N, M[MAXN][MAXN];

queue<pair<int, int>> q;

int bit_val(int n){
    return 1<<(n-1);
}

void queue_init(){
    for(int i=2; i<=N; i++){
        int bit = bit_val(i);
        if(M[1][i]) {
            D[i][bit] = M[1][i];
            q.push({i, bit});
        }
    }
}

void set_table() {
    int cost, mask;
    pair<int, int> cur;
    
    while(!q.empty()){
        cur = q.front(); q.pop();
        
        for (int next=2; next<=N; next++) {
            if (M[cur.first][next] ==0) continue;
            
            mask = cur.second;
            cost = D[cur.first][cur.second];
            
            if (!(mask & bit_val(next))) {
                cost += M[cur.first][next];
                mask |= bit_val(next);
                
                if (D[next][mask]==0) {
                    D[next][mask] = cost;
                    q.push({next, mask});
                }
                if (cost < D[next][mask]) D[next][mask] = cost;
            }
        }
    }
}

int result() {
    int mask = 0, ret = 999999999;
    
    for(int i=2; i<=N; i++) mask |= bit_val(i);
    
    for(int i=2; i<=N; i++) {
        int sum = M[i][1] + D[i][mask];
        if (sum< ret) ret = sum;
    }

    return ret;
}

int main() {
    
    cin>>N;
    
    for(int i=1; i<=N; i++){
        for(int j=1; j<=N; j++){
            cin>>M[i][j];
        }
    }
    queue_init();
    set_table();
    
    cout<<result()<<endl;
    
    return 0;
}
