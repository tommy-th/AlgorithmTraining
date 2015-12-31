#include <stdio.h>


int main(){

	int s[70000];
	int i,d,m, a,b,num;

	long long sum=0, sum1;

	scanf("%d %d",&d,&m);

	for(i=0; i<d ;i++){
		scanf("%d",&s[i]);
	}

	b = a = s[0]; 

	for(i=0; i<d; i++){
		if(s[i]>=b){
			b = s[i];
			num = m/a;
			sum1 = num*(b-a);
			if(sum1>sum)
				sum=sum1;
		}

		else if(s[i]<a){
			b = a = s[i];
		}

		else{
			b = s[i];
		}
	}

	printf("%lld\n",sum);
}