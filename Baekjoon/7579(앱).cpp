//
//  앱(7579).cpp
//  Baekjoon
//
//  Created by JangTaehwan on 2015. 12. 12..
//  Copyright © 2015년 JangTaehwan. All rights reserved.
//

#include <iostream>
using namespace std;

int N, M;
int memory[105], costs[105], D[10505];

int main(){
    
    int result = 10005;
    
    cin >> N >> M;
    for(int i = 1; i <= N; i++)
        cin >> memory[i];
    for(int i = 1; i <= N; i++)
        cin >> costs[i];
            
    for(int i = 1; i <= N; i++){
        for(int j = 10000; j >= 0; j--){
            if(D[j] + memory[i] > D[j+costs[i]]) D[j+costs[i]] = D[j] + memory[i];
        }
    }
    
    for(int i = 0; i <= 10000; i++){
        if(D[i] >= M){
            result = i;
            break;
        }
    }
    
    cout << result <<endl;
}
