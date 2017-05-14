#include <iostream>
#include <cstring>
using namespace std;

int N;
char gene[505];
int D[505][505];

void search(int s, int len){
	int temp ,max = 0;
	
	for (int i = 1; i < len; i ++){
		temp = D[s][s + i - 1] + D[s + i][s + len - 1];
		if (temp > max) max = temp;
	}
	if ((gene[s] == 'a' && gene[s + len - 1] == 't') || (gene[s] == 'g' && gene[s + len - 1] == 'c')){
		if (D[s + 1][s + len - 2] + 1 > max) max = D[s + 1][s + len - 2] + 1;
	}
	D[s][s + len - 1] = max;
}

void set_table(){

	for (int k = 2; k <= N; k ++){
		for (int i = 1; i <= N - k + 1; i++){
			search(i, k);
		}
	}
}

int main(){

	gene[0] = '0';
	cin >> &gene[1];
	N = strlen(gene) - 1;

	set_table();

	printf("%d\n", D[1][N]*2);

	return 0;
}