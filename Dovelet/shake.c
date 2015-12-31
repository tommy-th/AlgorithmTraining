#include <stdio.h>

int main(){

	int s[1000];
	int n, i, idx1, idx2, temp, high, low, count =0;

	scanf("%d",&n);
	
	high = n-1;
	low = 0;

	for(i=0; i<n; i++){
		scanf("%d", &s[i]);
	}

	while (high>low){

		i = idx1 = low;
		while(i < high){
			if (s[i] > s[i+1]){
				temp = s[i + 1];
				s[i + 1] = s[i];
				s[i] = temp;
				idx1 = i;
			}
			i++;
		}

		i = idx2 = high;
		while (i > low){
			if (s[i] < s[i - 1]){
				temp = s[i - 1];
				s[i - 1] = s[i];
				s[i] = temp;
				idx2 = i;
			}
			i--;
		}

		low = idx2;
		high = idx1;
		count++;
	}
	printf("\n%d\n", count);
}
