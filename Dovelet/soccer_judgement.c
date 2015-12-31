#include <stdio.h>

int main(){
	double sum=0.0,judge[101] = { 0, };
	int i, j, k, nation, judge_num, nation_num, point, number, result;

	scanf("%d %d", &nation, &judge_num);

	for (i = 1; i <= nation; i++){
		scanf("%d %d", &nation_num, &k);
		for (j = 1; j <= k; j++){
			scanf("%d %d", &number, &point);
			judge[number] += (double)point/nation_num;
		}
	}
	for (i = 1; i <= 100; i++){
		if (judge[i] > sum){
			sum = judge[i];
			result = i;
		}
	}
	printf("%d\n", result);
}