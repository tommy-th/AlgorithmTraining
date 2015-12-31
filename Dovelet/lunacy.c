#include <stdio.h>

int main(){

	double weight=0.0, result;

	while(weight>=0.0){
		scanf("%lf",&weight);

		result = weight*0.167;

		if(weight>0.0)
			printf("Objects weighing %.2lf on Earth will weigh %.2lf on the moon.\n", weight, result);

	}
}