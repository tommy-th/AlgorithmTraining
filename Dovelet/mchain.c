#include <stdio.h>

int main(){

	int s[1000];
	int a, b, c, t, mid, i=0, j, count=2;

	scanf("%d",&t);
	mid = t/2;

	while(mid <= t ){
		a = t;
		b = mid;

		while(a-b>=0){
			count++;
			c = a-b;
			a=b;
			b=c;
		}
		s[i++] = count;
		count = 2;
		mid++;
	}

	for(j=0; j<i; j++){
		if(s[0]<s[j])
			s[0] = s[j];
	}

	printf("%d\n",s[0]);
	
}
