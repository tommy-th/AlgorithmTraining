#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

int len[505][505], lists[505][505], results[505], D[505], P[505], cut[505][505];
int q[2][505], H[505], qidx, qidxNext;
int T, N, M, start, rIdx;

void searchNode(int n){
	int temp, next, parent;

	for (int i = 1; i <= lists[n][0]; i++){
		next = lists[n][i];
		temp = len[next][n] + D[n];
		if ((temp <= D[next] || D[next] == 0) && next != start){
			parent = P[next];
			if (temp == D[next] && parent != n) {
				parent = P[next];
				cut[parent][next] = cut[next][parent] = 1;
			}
			else{
				D[next] = temp;
				P[next] = n;
				cut[n][next] = cut[next][n] = 0;
			}
			if (H[next]) continue;
			H[next] = 1;
			q[qidxNext][0]++;
			q[qidxNext][q[qidxNext][0]] = next;
		}
	}
}

void searchLoop(){
	while (1){
		qidxNext = (qidx + 1) % 2;
		q[qidxNext][0] = 0;
		for (int i = 1; i <= q[qidx][0]; i++){
			searchNode(q[qidx][i]);
		}
		qidx = (qidx + 1) % 2;
		if (q[qidx][0] == 0) return;
		memset(H, 0, sizeof(H));
	}
}

void plusResults(){
	int parent;

	for (int i = 1; i <= N; i++){
		parent = P[i];
		if (parent != 0 && parent != start){
			if (cut[parent][i] == 0 && results[parent] == 0){
				results[parent] = 1;
				rIdx++;
			}
		}
	}
}

void calcResults(){
	for (int i = 1; i <= N; i++){
		start = i;
		memset(D, 0, sizeof(D));
		memset(P, 0, sizeof(P));
		memset(cut, 0, sizeof(cut));
		q[0][0] = 1;
		q[0][1] = i;
		searchLoop();
		plusResults();
	}
}

void reset(){
	for (int i = 0; i <= N; i++) lists[i][0] = 0;
	memset(results, 0, sizeof(results));
	rIdx = 0;
}

void print(){
	cout << rIdx << " ";
	for (int i = 1; i <= N; i++){
		if (results[i]) cout << i << " ";
	}
	cout << endl;
}

int main(){

	int a, b, temp;

	cin >> T;
	for (int t = 1; t <= T; t++){
		cin >> N >> M;

		reset();
		for (int i = 1; i <= M; i++){
			cin >> a >> b >> temp;
			len[a][b] = len[b][a] = temp;
			lists[a][0]++;
			lists[b][0]++;
			lists[a][lists[a][0]] = b;
			lists[b][lists[b][0]] = a;
		}
		calcResults();

		printf("Case #%d\n", t);
		print();
	}

	return 0;
}