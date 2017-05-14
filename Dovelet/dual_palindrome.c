#include <stdio.h>

int pal_num(int s, int n){
	int temp = n, p1 = s, p2 = 1;

	while (p1 <= n) p1 *= s;
	p1 /= s;

	while (1){
		if (p1 == p2) return 1;
		if ((temp % (p1*s)) / p1 != (temp % (p2*s)) / p2) return 0;
		p1 /= s;
		p2 *= s;
		if (p2 > p1) return 1;
	}
	return 0;
}

int main(){
	int i, n, s, c=0, u=0;

	scanf("%d %d", &n, &s);

	while (1){
		s++;
		for (i = 2; i <= 10; i++){
			if (pal_num(i, s)) c++;
		}
		if (c >= 2){
			printf("%d\n", s);
			u++;
			if (u == n) break;
		}
		c = 0;
	}
	
	return 0;
}