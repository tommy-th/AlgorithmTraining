//
//  11493 - A(Hungarian method).cpp
//  AlgorithmTraining
//
//  Created by JangTaehwan on 2016. 1. 3..
//  Copyright © 2016년 JangTaehwan. All rights reserved.
//

#include <iostream>
#include <cstring>
#include <queue>
#include <list>
using namespace std;

#define MAXN 505
#define INF 100000
queue<int> q;
int N, M;

int  color[505], node[505][505], dp[505], start;
int bn, circles[505], squares[505], dis[505][505], table[505][505];

void AddToTree(int, int);
void UpdateLabels();

int cost[MAXN][MAXN];  // cost matrix
int max_match  = 0;  // if max_match is N, we are done
int label_x[MAXN], label_y[MAXN];  // vertex labels
int xy[MAXN];  // xy[x] - vertex in Y matched with x
int yx[MAXN];  // yx[x] - vertex in X matched with y
bool S[MAXN], T[MAXN];  // Helps find augmenting path
int slack[MAXN];  // helps update label
int slackx[MAXN]; // slack[y] -> x such that l(x) + l(y) - w(x,y) = slack[y]
int previous[MAXN];  // for memorizing alternating paths

void reset(){
    memset(node, 0, sizeof(node));
    memset(color, 0, sizeof(color));
    memset(dis, 0, sizeof(dis));
    memset(table, 0, sizeof(table));
    memset(squares, 0, sizeof(squares));
    memset(circles, 0, sizeof(circles));
    bn = 0;
}

void insertNode(int n, int val){
    int idx = ++node[n][0];
    node[n][idx] = val;
}

void searchPoint(int n, int cnt){
    int a, b, next;
    
    for (int i=1; i<=node[n][0]; i++) {
        next = node[n][i];
        if (next == start) continue;
        if (dp[next] == 0 || cnt + 1 < dp[next]){
            dp[next] = cnt + 1;
            
            if(color[next]==2){
                a = circles[start];
                b = squares[next];
                dis[a][b] = cnt + 1;
            }
            q.push(next);
        }
    }
}

void setDistance(){
    for(int i=1; i<=N; i++){
        start = i;
        if (color[start] != 1) continue;
        memset(dp, 0, sizeof(dp));
        q.push(i);
        while(!q.empty()){
            searchPoint(q.front(), dp[q.front()]);
            q.pop();
        }
    }
}

void InitLabels() {
    memset(label_x, 0, sizeof(label_x));
    memset(label_y, 0, sizeof(label_y));
    for (int x=0; x<N; x++) {
        for (int y=0; y<N; y++) {
            label_x[x] = max(label_x[x], cost[x][y]);
        }
    }
}

void Augment() {
    if (max_match == N) return; // check if matching is perfect
    int x, y, root = 0;
    int q[MAXN], wr = 0, rd = 0;
    
    memset(S, false, sizeof(S));
    memset(T, false, sizeof(T)); // init S, T
    memset(previous, -1, sizeof(previous)); // init prev for the alternating tree
    // -1 means no prev. -2 means current is root
    
    // find ONE unmatched x and make it root
    for (x=0; x<N; x++) {
        // finding the exposed x in X and make it the root of the alternating tree
        if (xy[x] == -1) {
            // if x is unmatched
            q[wr++] = root = x;  // find roots of the tree
            previous[x] = -2;  // root has no prev
            S[x] = true;   // put x in S
            break;
        }
    }
    
    // initialize slack to save computations
    for (y=0; y<N; y++) {
        // Now T is empty, so we find all the slacks of y in Y
        slack[y] = label_x[root] + label_y[y] - cost[root][y]; // help find its min value
        // For all y, slackx[y] can be computed with root
        slackx[y] = root;
    }
    
    while (true) {
        // look for augmenting path
        while (rd < wr) {
            // iterating over all possible roots
            x = q[rd++];  // one root.   q is for building tree with bfs search
            for (y=0; y<N; y++) {
                if (cost[x][y] == label_x[x] + label_y[y] && !T[y]) { // for all edges
                    if (yx[y] == -1) break;  // an exposed vertex in Y found. augmenting path.
                    T[y] = true;  // add y to T
                    q[wr++] = yx[y];  //
                    AddToTree(yx[y], x);  // put yx[y] in S because y is matched to yx[y]
                }
            }
            if (y<N) break;
        }
        if (y<N) break;
        
        // Execute the following code only if we fail to find an augmenting path
        
        UpdateLabels();
        wr = rd = 0;
        
        // We have updated the labels, but we still need to add edges to the tree
        // y is the newly added element to improve the labeling
        for (y=0; y<N; y++) {
            if (!T[y] && slack[y] == 0) {  // augmenting path
                if (yx[y] == -1) {  // not matched
                    x = slackx[y];
                    break;
                }
                else {
                    T[y] = true;  // y is matched
                    if (!S[yx[y]]) {  // if the one matched to y, r, is not in S
                        q[wr++] = yx[y];  // put r in q
                        // Add r and the v which minimizes l(y)
                        AddToTree(yx[y], slackx[y]);
                    }
                }
            }
        }
        if (y < N) break;
    }
    
    // augmenting path found, reverse all edges along the path
    if (y<N) {
        max_match++;  // increment
        // y is the unconnected vertex, the target of the augmenting path
        // x is slackx[y]
        // we traverse backward until cx == -2 which is the root
        for (int cx=x, cy=y, ty; cx != -2; cx = previous[cx], cy =ty) {
            ty = xy[cx];  // ty is connected with cx (current x)
            yx[cy] = cx;
            xy[cx] = cy;  // connect cx and cy
        }
        Augment();
    }
}

void UpdateLabels() {
    int x, y, delta = INF;
    for (y=0; y<N; y++) {
        if (!T[y])  // y not in T
            delta = min(delta, slack[y]);  // find the minimum
    }
    for (x=0; x<N; x++)
        if (S[x]) label_x[x] -= delta;
    for (y=0; y<N; y++)
        if (T[y]) label_y[y] += delta;  // update x in S, y in T
    for (y=0; y<N; y++)
        if (!T[y])
            slack[y] -= delta;  // This is because l(x) is delta less, l(y) is constant
}


void AddToTree(int x, int prevx) {
    // x     - current vertex
    // prevx - vertext from X before x in the alternating path
    S[x] = true;  // add x to S
    previous[x] = prevx;  // put it in the alternating path
    for (int y=0; y<N; y++) {
        if (label_x[x] + label_y[y] - cost[x][y] < slack[y]) {
            // update slack because we added a new element to S
            // because slack[y] will always be the minimum from y to ANY element x in X
            slack[y]  = label_x[x] + label_y[y] - cost[x][y];
            slackx[y] = x;
        }
    }
}


int Hungarian() {
    int result = 0;
    max_match  = 0;
    memset(xy, -1, sizeof(xy));
    memset(yx, -1, sizeof(yx)); // initially, no elements are connected
    InitLabels();
    Augment();
    for (int x=0; x<N; x++) {
        //  cout << x << " is connected to " << xy[x] << endl;
        result += cost[x][xy[x]]; // add up the corresponding costs
    }
    return result;
}


void ReadMatrixFromInput() {
    N = bn;
    for (int row=0; row<N; row++) {
        for (int col=0; col<N; col++) {
            cost[row][col] = dis[row+1][col+1];
        }
    }
}

int FindLargestInMatrix(int A[MAXN][MAXN]) {
    int largest = A[0][0];
    for (int row=0; row<N; row++) {
        for (int col=0; col<N; col++) {
            if (A[row][col] >= largest) {
                largest = A[row][col];
            }
        }
    }
    return largest;
}

void ProcessMatrix(int A[MAXN][MAXN], int largest) {
    for (int row=0; row<N; row++) {
        for (int col=0; col<N; col++) {
            A[row][col] = largest - A[row][col];
        }
    }
}

int main() {
    
    int testcase, largest, a, b, c;
    
    cin>>testcase;
    for ( int t=1; t<=testcase; t++){
        
        reset();
        
        cin>>N>>M;
        for(int i=1; i<=M; i++){
            cin >> a >> b;
            insertNode(a , b);
            insertNode(b , a);
        }
        
        // circles color
        for(int i=1; i<=N; i++){
            cin >> c;
            if (c) {
                bn++;
                color[i] = 1;
            }
        }
        
        // squares color
        for(int i=1; i<=N; i++){
            cin >> c;
            if (c) {
                if (color[i]){
                    bn--;
                    color[i] =0;
                }
                else color[i] = 2;
            }
        }
        
        for(int i=1; i<=N; i++){
            if (color[i]==1){
                ++circles[0];
                circles[i] = circles[0];
            }
            if(color[i]==2){
                ++squares[0];
                squares[i] = squares[0];
            }
        }
        setDistance();
        
        ReadMatrixFromInput();
        largest = FindLargestInMatrix(cost);
        ProcessMatrix(cost, largest);
        cout << N*largest - Hungarian() << endl;
    }
    
    return 0;
}