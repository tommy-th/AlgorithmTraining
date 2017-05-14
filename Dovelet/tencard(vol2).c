#include <stdio.h>

int rotate(int n){
	return (n % 1000) * 10 + n / 1000;
}

int detect(int n){
	int i, temp = n;
	if (n < 1111 || n > 9999) return 0;
	for (i = 0; i<3; i++){
		temp = rotate(temp);
		if (n > temp) return 0;
	}
	return 1;
}

int clocknum(int n){
	int i, t1, t2, count = 0;

	t1 = t2 = n;

	for (i = 0; i < 3; i++){
		t1 = rotate(t1);
		if (t2 > t1) t2 = t1;
	}

	for (i = 1111; i < 10000; i++){
		if (detect(i)){
			count++;
			if (t2 == i) return count;
		}
	}
	return 0;
}

int main(){

	int a,b,c,d; 
	scanf("%d%d%d%d", &a, &b, &c, &d);
	printf("%d\n", clocknum(a * 1000 + b * 100 + c * 10 + d));

	return 0;
}