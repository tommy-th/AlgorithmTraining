#include <stdio.h>

int main(){

	int i,n, a[7], b[7],sum, result =0,j=0;


	scanf("%d",&n);

	for(i=0; i<n; i++){

		scanf("%d %d",&a[i],&b[i]);

		if(a[i]+b[i]>8)
			sum = a[i]+b[i];
		if(sum>result){
			result = sum;
			j=i+1;		
		}
	}

	printf("%d\n",j);
}