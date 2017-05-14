#include <stdio.h>

int main(){


	int prison[100000];

	int n,i,j,sum=0;

	scanf("%d",&n);

	for(i=0; i<n; i++){

		if(i==0){
			for(j=0;j<n;j++){
				prison[j] = 0;
			}
			prison[i] = 3;
		}

		else if(i==1){
			for(j=2;j<n;j++){
				if(j%2==1)
					prison[j] = 1;
			}
			prison[i] = 3;
		}

		else{
			if(prison[i]==0){
				prison[i] = 3;
				for(j=(i+1)*2; j<n+1; j+=i+1){
					prison[j-1] = (prison[j-1]+1)%2;
				}
			}
		}
	}

	for(i=0; i<n; i++){
		if(prison[i] == 3)
			sum++;
	}

	printf("%d\n",sum);
}