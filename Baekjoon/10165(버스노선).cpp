//
//  버스노선(10165).cpp
//  Baekjoon
//
//  Created by JangTaehwan on 2015. 12. 20..
//  Copyright © 2015년 JangTaehwan. All rights reserved.
//

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct node{
    int n, a, b;
    
    node(int n, int a, int b) : n(n), a(a), b(b) {}
};

int N, M, R[500005];
//vector<pair<int, int>> lineList;
vector<node> lineList;

void searchLoop(){
    int idx = 0, point;
    
    point= lineList[idx].b;
    for(int i=1; i<M; i++){
        if(lineList[i].b > point){
            idx = i;
            point = lineList[i].b;
        }
        else{
            R[lineList[i].n] = 1;
        }
    }

    int i=0;
    while(lineList[idx].b - N >= lineList[i].b) {
        R[lineList[i].n] = 1;
        i++;
    }
}

void printResult(){
    for(int i=0; i<M; i++){
        if(!R[i]) cout<<i+1<<" ";
    }
    cout<<endl;
}

int main(){
    
    int a, b;
    cin >> N >> M;
    
    for(int i = 0; i < M; i++){
        cin >> a >> b;
        b = b < a ? b+N : b;
        lineList.push_back(node(i, a, b));
    }

//    sort(lineList.begin(), lineList.end(), [](pair<int, int>& a, pair<int, int>& b){
//        return (a.first < b.first || ((a.first==b.first) && (a.second > b.second)));
//    });
    sort(lineList.begin(), lineList.end(), [](const node& line1,const node& line2){
        return (line1.a < line2.a || ((line1.a==line2.a) && (line1.b > line2.b)));
    });

//    for(int i=0; i < M; i++){
//        cout<<lineList[i].n <<" "<<lineList[i].a <<" " <<lineList[i].b<<endl;
//    }

    searchLoop();
    printResult();
    
    return 0;
}
