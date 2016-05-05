//
//  10158(개미).cpp
//  AlgorithmTraining
//
//  Created by Jang on 2016. 5. 3..
//  Copyright © 2016년 JangTaehwan. All rights reserved.
//

#include <iostream>
using namespace std;

int W, H;

int y, x, t;

const int next_point[4][2] = {{1, 1}, {1, -1}, {-1, -1}, {-1, 1}};
const int next_dir[4][3] = {{3, 1, 2}, {2, 0, 3}, {1, 3, 0}, {0, 2, 1}};

void move_ant(){
    int nx, ny;
    int dir_idx = 0;
    
    while(t){
        ny = y + next_point[dir_idx][0];
        nx = x + next_point[dir_idx][1];
        
        if((ny<0 || ny>H) && (nx<0 || nx>W)) dir_idx = next_dir[dir_idx][2];
        else if(ny<0 || ny>H) dir_idx =next_dir[dir_idx][0];
        else if(nx<0 || nx>W) dir_idx = next_dir[dir_idx][1];
        else{
            t--;
            y = ny, x = nx;
        }
    }
}

int main(){
    
    cin>>W>>H;
    cin>>x>>y;
    cin>>t;
    
    move_ant();
    cout<<x<<" "<<y<<endl;
    
    return 0;
}
