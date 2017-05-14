#include <stdio.h>

int main(){

	int result[1000];
	int n, sum=0, sum1=0, i=1, j=0, k;

	scanf("%d",&k);

	for(n=220; n<k; n++){
	
		while(i<n){
			if(n%i==0)
				sum += i;
			i++;
		}

		i=1;
		while(i<sum){
			if(sum%i==0)
				sum1 += i;
			i++;
		}
		i=1;

		if(sum1==n && n<sum){
			result[j] = n;
			result[j+1] = sum;
			j+=2;
		}

		sum=0;
		sum1=0;

	}
	
	for(i=0; i<j; i += 2){
		printf("%d %d\n", result[i], result[i+1]);
	}

}
