//
//  2110(공유기 설치).cpp
//  AlgorithmTraining
//
//  Created by Jang on 2016. 3. 26..
//  Copyright © 2016년 JangTaehwan. All rights reserved.
//

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int N, C;
int result;
vector<int> houses;

bool check_distance(int dis){
    
    int state, count = C;
    
    state = houses[0];
    count--;
    
    for(int i=1; i<houses.size(); i++){
        if(houses[i] >= state + dis){
            state = houses[i];
            count--;
        }
        if (count==0){
            result = max(result, dis);
            break;
        }
    }
    
    return count == 0;
}

void bsearch(){
    int min = 1, max = 1000000000;
    
    while(min != max){
        int mid = (min + max) / 2;
        
        if(check_distance(mid)) min = mid+1;
        else max = mid;
    }
    check_distance(min);
}


int main(){
    
    int location;
    
    cin >> N >> C;
    
    for(int i=1; i<=N; i++){
        cin>>location;
        houses.push_back(location);
    }
    
    sort(houses.begin(), houses.end());
    bsearch();
    
    cout<< result <<endl;
    
    return 0;
}
