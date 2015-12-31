#include <stdio.h>

int main(){

	double t[101], temp;
	int n, i, j, s1[101], s2[101], u1, u2, u3=-1, u4=-1, on = 0;

	scanf("%d", &n);

	printf("0/1\n");

	for (i = 1; i <= n; i++){
		s1[i] = 1;
		s2[i] = i;
		t[i] = (double)s1[i] / s2[i];
	}

	while (on==0){

		temp = t[n]; j = n;
		for (i = 1; i < n; i++){
			if (t[i] < temp){
				temp = t[i];
				j = i;
			}
		}
		u1 = s1[j];
		u2 = s2[j];
		s1[j]++;
		t[j] = (double)s1[j] / s2[j];
		for (i = 2; i <= s1[j]; i++){
			while (u1 % i == 0 && u2 % i == 0){
				u1 /= i;
				u2 /= i;
			}
		}	

		if (u1 != u3 || u2 != u4){
			printf("%d/%d\n", u1, u2);
			u3 = u1; u4 = u2;
		}

		if (u1 == u2) on = 1;
	}
}