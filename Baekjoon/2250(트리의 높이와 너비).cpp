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
int child[10005][2], parent[10005], info[10005][2];
int root, point;
int pwidth, plevel, leaf;

void set_root(){
    int cur = root;
    
    while(parent[cur]){
        cur = parent[cur];
    }
    root = cur;
}

void set_width(int y, int x){
    if(info[y][0] == 0 || x < info[y][0]) info[y][0] = x;
    if(info[y][1] == 0 || x > info[y][1]) info[y][1] = x;
}

void inorder(int n, int level){
    if(child[n][0]) inorder(child[n][0], level+1);
    set_width(level, ++point);
    leaf = max(leaf, level);
    if(child[n][1]) inorder(child[n][1], level+1);
}

void set_result() {
    
    for(int i=1; i<=leaf; i++){
        int width = info[i][1] - info[i][0] + 1;
        if(width > pwidth){
            plevel = i;
            pwidth = width;
        }
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
    
    inorder(root, 1);
    
    set_result();
    
    cout<<plevel<<" "<<pwidth<<endl;

    return 0;
}