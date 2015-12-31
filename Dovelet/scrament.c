#include <stdio.h>

int main(){

	int c1[50000], c2[50000];
	int a,b,i,j=0,s=0;

	scanf("%d",&a);
	for(i=0;i<a;i++)
		scanf("%d",&c1[i]);
	
	scanf("%d",&b);
	for(i=0;i<b;i++)
		scanf("%d",&c2[i]);

	for(i=0; i<a; i++){
		while((c1[i]+c2[j])>=10000){
			if(c1[i]+c2[j]==10000)
				s=1;
			j++;
		}
	}

	if(s)
		printf("YES\n");
	else
		printf("NO\n");

}