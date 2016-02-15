//
//  MyHungarian.cpp
//  AlgorithmTraining
//
//  Created by JangTaehwan on 2016. 1. 10..
//  Copyright © 2016년 JangTaehwan. All rights reserved.
//
// Reference from
// https://github.com/pavelkang/Hungarian/blob/master/robot.cpp
//

#include <iostream>
#include <list>
#include <queue>
using namespace std;

list<pair<int, int>> zeros, ans;
int bn, table[505][505], dis[505][505], row[505], col[505], lrow[505], lcol[505];
int hyx[505][505], hy[505], hx[505];

void resetHash(){
    memset(row, 0, sizeof(row));
    memset(col, 0, sizeof(col));
    memset(hyx, 0, sizeof(hyx));
    memset(hy, 0, sizeof(hy));
    memset(hx, 0, sizeof(hx));
    zeros.clear();
    ans.clear();
}

void insertZero(int y, int x){
    zeros.push_back(make_pair(y, x));
    row[y]++, col[x]++;
}

void setTable() {
    int min;
    
    resetHash();
    for(int i=1; i<=bn; i++){
        min = 99999;
        for(int j=1; j<=bn; j++){
            if(dis[i][j]<min) min = dis[i][j];
        }
        for(int j=1; j<=bn; j++){
            table[i][j] = dis[i][j] - min;
            if(table[i][j]==0) insertZero(i, j);
        }
    }
    for(int j=1; j<=bn; j++){
        min = 99999;
        for(int i=1; i<=bn; i++){
            if(table[i][j]<min) min = table[i][j];
        }
        if (min==0) continue;
        for(int i=1; i<=bn; i++){
            table[i][j] = table[i][j] - min;
            if(table[i][j]==0) insertZero(i, j);
        }
    }
}

void setAns() {
    pair<int, int> pt;
    
    while(!zeros.empty()){
        int isIn = 0;
        list<pair<int,int>>::iterator iter = zeros.begin();
        
        while(iter != zeros.end()){
            pt = *iter;
            
            if (hy[pt.first] || hx[pt.second]) {
                isIn = 1;
                row[pt.first]--, col[pt.second]--;
                zeros.erase(iter++);
            }
            else if (row[pt.first] == 1 || col[pt.second] == 1) {
                isIn = 1;
                row[pt.first]--, col[pt.second]--;
                hyx[pt.first][pt.second] = hy[pt.first] = hx[pt.second] = 1;
                ans.push_back(pt);
                zeros.erase(iter++);
            }
            else iter++;
        }
        if(isIn==0){
            pt = zeros.front();
            zeros.pop_front();
            row[pt.first]--, col[pt.second]--;
            hy[pt.first] = hx[pt.second] = 1;
            ans.push_back(pt);
        }
    }
}

void lineRow(int);

void lineCol(int x){
    if(lcol[x]) return;
    lcol[x] = 1;
    for(int i=1; i<=bn; i++){
        if(hyx[i][x]) lineRow(i);
    }
}

void lineRow(int y){
    if(lrow[y]) return;
    lrow[y] = 1;
    for(int j=1; j<=bn; j++){
        if(table[y][j]==0) lineCol(j);
    }
}


void printTable(){
    cout<<endl;
    for(int i=1; i<=bn; i++){
        for(int j=1; j<=bn; j++){
            cout<<table[i][j]<<" ";
        }
        cout<<endl;
    }
}

void resetTable(){
    int min = 99999;
    
    resetHash();
    
    for(int i=1; i<=bn; i++){
        for(int j=1; j<=bn; j++){
            if(lcol[j] || !lrow[i]) continue;
            else if (table[i][j]<min) min = table[i][j];
        }
    }
    
    for(int i=1; i<=bn; i++){
        for(int j=1; j<=bn; j++){
            if(lcol[j] && !lrow[i]) table[i][j] += min;
            else if(lcol[j] || !lrow[i]);
            else table[i][j] -= min;
            
            if(table[i][j]==0){
                insertZero(i, j);
            }
        }
    }
}

int getResult(){
    list<pair<int,int>>::iterator iter;
    int result = 0;
    
    setTable();
    printTable();
    setAns();
    while (ans.size() < bn){
        memset(lrow, 0, sizeof(lrow));
        memset(lcol, 0, sizeof(lcol));
        
        for(int i=1; i<=bn; i++){
            if(!hy[i]) lineRow(i);
        }
        resetTable();
        printTable();
        setAns();
    }
    
    for(iter = ans.begin(); iter != ans.end(); ++iter){
        result += dis[(*iter).first][(*iter).second];
    }
    return result;
}

int main(){
    
    cin>>bn;
    
    for(int i=1; i<=bn; i++){
        for(int j=1; j<=bn; j++){
            cin>>dis[i][j];
        }
    }
    cout<<getResult()<<endl;
    
    return 0;
}
