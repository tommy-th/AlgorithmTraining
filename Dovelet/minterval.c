#include <stdio.h>

int main(){

	long long int sum = 0;
	long long int sum1 = 0;
	long long int sum2 = 0;
	int a[2000], i=-1,j;
	int nega=-1;

	do{
		i++;
		scanf("%d",&a[i]);

		if(a[i]>0){
			sum1+=a[i];
			nega=0;
		}
		else{
			if(sum1>sum)
				sum = sum1;
			sum1 = 0;
		}

		if((sum2+a[i])>0){
			sum2 += a[i];
			if(sum2>sum)
				sum = sum2;
			nega=0;
		}
		else{
			sum2 = 0;
		}

	}while(a[i] != 0);

	if(nega==-1){
		sum = a[0];
		for(j=1;j<i;j++){
			if(a[j]>sum)
				sum = a[j];
		}
	}

	printf("%lld\n",sum);

	return 0;
}