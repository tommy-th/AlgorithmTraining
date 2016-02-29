//
//  트리의 높이와 너비(2250).cpp
//  AlgorithmTraining
//
//  Created by JangTaehwan on 2016. 2. 29..
//  Copyright © 2016년 JangTaehwan. All rights reserved.
//

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int N;
int child[10005][2], parent[10005];
int root, point;
int max_width, max_level;

vector<pair<int, int>> info;

void set_root(){
    int cur = root;
    
    while(parent[cur]){
        cur = parent[cur];
    }
    root = cur;
}

void push_node(int n, int level){
    if(child[n][0]) push_node(child[n][0], level+1);
    info.push_back({level, ++point});
    if(child[n][1]) push_node(child[n][1], level+1);
}

void set_result() {
    int level = 1, left, right;
    
    left = right = info[0].second;
    
    for(int i=1; i<info.size(); i++){
        
        if(info[i].first != level){
            int temp = right - left + 1;
            
            if(max_width < temp) {
                max_width = temp;
                max_level = level;
            }
            level = info[i].first;
            left = info[i].second;
        }
        
        right = info[i].second;
    }
    
    int temp = right - left + 1;
    
    if(max_width < temp) {
        max_width = temp;
        max_level = level;
    }
}

int main() {

    int n, a, b;
    
    cin>> N;
    
    for(int i=1; i<=N; i++){
        cin>>n;
        cin>>a>>b;
        
        if(root==0) root = n;
        
        if(a>0){
            parent[a] = n;
            child[n][0] = a;
        }
        if(b>0){
            parent[b] = n;
            child[n][1] = b;
        }
    }
    
    set_root();
    push_node(root, 1);
    
    sort(info.begin(), info.end(), [](pair<int, int> a, pair<int, int> b){
        return a.first < b.first || (a.first==b.first && a.second<b.second);
    });
    
    set_result();
    
    cout<<max_level<<" "<<max_width<<endl;

    return 0;
}