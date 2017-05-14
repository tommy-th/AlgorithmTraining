#include <stdio.h>

int M, N, X, Y;

int dif(){
	int result = M;
	while (result - N > 0){
		result -= N;
	}
	return result;
}

int result(){
	long long int result = X;
	int sub = X, dis, idx = -1, c = 0;
	dis = dif();

	while (sub != Y){
		c++;
		result += M;
		sub += dis;
		while (sub > N) sub -= N;
		if (c == N) idx = sub;
		else if (idx == sub && idx != -1) 
			return -1;
	}

	return result;
}

int main(){

	int i, j, t, buf;

	scanf("%d", &t);

	for (i = 0; i < t; i++){
		scanf("%d %d %d %d", &M, &N, &X, &Y);
		if (X > Y){
			buf = Y;
			Y = X;
			X = buf;
			buf = M;
			M = N;
			N = buf;
		}
		printf("%d\n", result());
	}


	return 0;
}