#include <stdio.h>
#include <math.h>

int main(){

	int c, n, i, j, idx1, idx2, on;
	long long int a, b, temp;


	scanf("%d", &n);

	for (j = 2; j <= n / 2; j++){
		on = 1;
		b = a = j;
		temp = n;

		while (b*j < temp){
			b *= j;
		}
	

		while (temp>0){
			if (a > b)
				break;
			idx1 = temp / b;
			idx2 = (temp % a)/(a/j);

			temp -= b * idx1;
			temp -= idx2*(a / j);
			
			b /= j;
			a *= j;

			if (idx1 != idx2){
				on = 0;
			}
			if (on == 0)
				break;
		}
	
		if (on) printf("%d\n", j);
	}

	printf("%d\n", n - 1);

	return 0;
}

