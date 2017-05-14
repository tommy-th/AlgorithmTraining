#include <stdio.h>

int main(){

	int n, m, count=0, i=0;

	scanf("%d",&n);

	m = n/5;

	for(i=0;i<m;i++){
		if((n-(m-i)*5)%3==0){
			count=m-i;
			break;
		}
	}

	n -= count*5;

	if(count==0 && n%3 !=0 )
		printf("-1\n");
	else
		printf("%d\n",count+n/3);
}