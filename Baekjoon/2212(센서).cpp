//
//  2212(센서).cpp
//  AlgorithmTraining
//
//  Created by Jang on 2016. 3. 27..
//  Copyright © 2016년 JangTaehwan. All rights reserved.
//

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define LL long long


int N, K;

vector<int> sensors;
vector<int> difs;

LL result;

int main(){
    
    int dis;
    
    cin >> N >> K;
    
    for(int i=1; i<=N; i++) {
        cin>>dis;
        sensors.push_back(dis);
    }
    
    sort(sensors.begin(), sensors.end());
    
    for(int i=1; i<sensors.size(); i++){
        difs.push_back(sensors[i]-sensors[i-1]);
        result += sensors[i] - sensors[i-1];
    }
    
    sort(difs.begin(), difs.end(), [](int a, int b){
        return a > b;
    });
    
    if(K >= N){
        result = 0;
    }
    else{
        for(int i=0; i<K-1; i++){
            result -= difs[i];
        }
    }
    
    cout<<result<<endl;
    
    return 0;
}