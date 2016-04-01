//
//  2826(함수의 리턴값).cpp
//  AlgorithmTraining
//
//  Created by Jang on 2016. 3. 31..
//  Copyright © 2016년 JangTaehwan. All rights reserved.
//

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

#define LL long long 
#define MOD 1000000007

const int lmax = 100000;

int test();

int N;
int loop[30][2];
int var[30][2];

int check[30];

LL dp[30][100005];
LL sum[30][100005];
LL result = -1;

vector<int> childs[30];


void mul_result(LL val){
    if(result < 0) result = val;
    else result = (result*val) % MOD;
}

void add_not_related(){
    for(int i=1; i<=N; i++){
        if(var[i][0]==0 && var[i][1]==0 && childs[i].empty()){
            mul_result(loop[i][1]-loop[i][0]+1);
            check[i] = 1;
        }
    }
}

void mul_table(int parent, int index, int child, int a, int b){
    
    LL sub_sum = sum[child][b] - sum[child][a];
    if(sub_sum < 0) sub_sum += MOD;
    dp[parent][index] = (dp[parent][index] * sub_sum) % MOD;
}

void check_boundary(int parent, int index, int child){
    int a, b;
    
    if(var[child][0] == parent){
        if(index > loop[child][1]){
            dp[parent][index] = 0;
            return;
        }
        
        a = index - 1, b = loop[child][1];
        
        mul_table(parent, index, child, a, b);
    }
    else if(var[child][1] == parent){
        if(index < loop[child][0]){
            dp[parent][index] = 0;
            return;
        }
        
        a = loop[child][0]-1, b = index;
        
        mul_table(parent, index, child, a, b);
    }
}

void set_table(int n){
    
    if(check[n]) return;
    check[n] = 1;
    
    for(int i=0; i<childs[n].size(); i++) set_table(childs[n][i]);
    
    for(int i=1; i<=lmax; i++)
        for(int j=0; j<childs[n].size(); j++)
            check_boundary(n, i, childs[n][j]);
    
    for(int i=1; i<=lmax; i++)
        sum[n][i] = (sum[n][i-1]+dp[n][i]) % MOD;
}

void loop_table(){
    int a, b;
    LL sub_sum;
    
    for(int i=1; i<=N; i++){
        if(check[i]) continue;
        set_table(i);
        
        a = loop[i][0]-1, b = loop[i][1];
        sub_sum = sum[i][b] - sum[i][a];
        if(sub_sum < 0) sub_sum += MOD;
        
        mul_result(sub_sum);
    }
}

int main(){
    
    string input;
    
    for(int i=0; i<30; i++){
        for(int j=0; j<100005; j++) dp[i][j] = 1;
    }
    
    cin>>N;
    getline(cin, input);
    
    for(int i=1; i<=N; i++){
        getline(cin, input);
        
        istringstream iss(input);
        for(int j=0; j<2; j++){
            string split;
            iss >> split;
            int value = atoi(split.c_str());
            
            if(value == 0){
                var[i][j] = split[0]-96;
                childs[var[i][j]].push_back(i);
            }
            else loop[i][j] = value;
        }
    }
    
    add_not_related();
    loop_table();
    
    cout<<result<<endl;
    
    return 0;
}

