#include <stdio.h>

int num_idx(int num, int idx){
	if(idx<=1)
		return num;
	else
		return num*num_idx(num,idx-1);
}

int main(){

	int m[100];
	int i, n, idx, sum=0;

	scanf("%d %d",&n,&idx);

	for(i=0; i<n; i++){
		scanf("%d",&m[i]);
		m[i] = num_idx(m[i],idx);
		if(m[i]>0)
			sum += m[i];
	}

	printf("%d\n",sum);

}