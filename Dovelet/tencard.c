#include <stdio.h>

int thousand(int a, int b, int c, int d){
	int s = a * 1000 + b * 100 + c * 10 + d; 
	return s;
}

int clock_num(int s[5]){
	int clocknum = 9999;

	if (thousand(s[1], s[2], s[3], s[4]) < clocknum)
		clocknum = thousand(s[1], s[2], s[3], s[4]);
	if (thousand(s[2], s[3], s[4], s[1]) < clocknum)
		clocknum = thousand(s[2], s[3], s[4], s[1]);
	if (thousand(s[3], s[4], s[1], s[2]) < clocknum)
		clocknum = thousand(s[3], s[4], s[1], s[2]);
	if (thousand(s[4], s[1], s[2], s[3]) < clocknum)
		clocknum = thousand(s[4], s[1], s[2], s[3]);

	return clocknum;
}

int main(){

	int i,j,n,m,idx=0;
	int s[5], clocknum, all[2000];

	all[0] = 0;

	for (i = 1; i < 10; i++){
		for (j = i; j < 10; j++){
			for (n = i; n < 10; n++){
				for (m = i; m < 10; m++){
					s[1] = i; s[2] = j; s[3] = n; s[4] = m;
					if (clock_num(s)>all[idx]){
						idx++;
						all[idx] = clock_num(s);
					}
				}
			}
		}
	}

	for (i = 1; i <= 4; i++)
		scanf("%d", &s[i]);
	clocknum = clock_num(s);

	for (i = 1; i < 1750; i++){
		if (clocknum == all[i]){
			printf("%d\n", i);
			break;
		}
	}

	return 0;
}