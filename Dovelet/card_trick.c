#include <stdio.h>

int main(){

	int arr[15] = {0,};
	int n, i, j, idx=0;

	scanf("%d",&n);

	for(i=0; i<n; i++){
		j=i+1;

		while(j>0 || arr[idx]!=0){
			if(arr[idx]==0){
				j--;
			}
			idx = (idx+1) % n;
		}

		arr[idx] = i+1; 
	}

	for(i=0; i<n; i++)
		printf("%d ",arr[i]);

	printf("\n");
}