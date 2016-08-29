//
//  1939(중량제한).cpp
//  AlgorithmTraining
//
//  Created by Jang on 2016. 8. 29..
//  Copyright © 2016년 JangTaehwan. All rights reserved.
//

#include <iostream>
#include <queue>
#include <vector>
using namespace std;

#define MAXN 10005

int N, M;
int spoint, epoint;

vector<pair<int, int>> edges[MAXN];

int max_weight;

int check_weight(int weight){
    int visit[MAXN] = {0,};
    
    queue<int> q;
    q.push(spoint);
    visit[spoint] = 1;
    
    while(!q.empty()){
        int node = q.front(); q.pop();
        
        for(int i=0; i<edges[node].size(); i++){
            int next = edges[node][i].first;
            int bridge = edges[node][i].second;
            
            if(bridge >= weight && visit[next] == 0){
                if(next==epoint){
                    max_weight = weight;
                    return 1;
                }
                
                visit[next] = 1;
                q.push(next);
            }
        }
    }
    
    return 0;
}

void bsearch(){
    int min = 1, max = 1000000000;
    
    while(min != max){
        int mid = (min + max) / 2;
        
        if(check_weight(mid)) min = mid+1;
        else max = mid;
    }
    check_weight(min);
}

int main(){
    
    int a, b, c;
    
    cin>>N>>M;
    
    for(int i=1; i<=M; i++){
        cin>>a>>b>>c;
        
        edges[a].push_back(make_pair(b, c));
        edges[b].push_back(make_pair(a, c));
    }
    
    cin>>spoint>>epoint;
    
    bsearch();
    cout<<max_weight<<endl;
    
    return 0;
}
