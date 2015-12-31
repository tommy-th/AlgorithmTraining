#include <stdio.h>
#include <math.h>


int verify(long long int n, long long int t, long long int b){
	long long int i = 1 , temp = b;
	int on = -1;
	
	while (i <= t && i <= sqrt(b)){
		if (b % i == 0){
			on *= -1;
			if (t >= n + i)	on *= -1;
			if (b / i != sqrt(b) && t >= b / i){
				on *= -1;
				if (t >= n + b / i) on *= -1;
			}
		}
		i++;
	}

	return on;
}

int main(){

	long long int n, t, b, c = 1;
	int result;

	while (scanf("%lld %lld %lld", &n, &t, &b) != EOF){
		t %= 2 * n;
		result = verify(n, t, b);
		if (result == 1) printf("Case %lld: On\n", c);
		else printf("Case %lld: Off\n",c);
		c++;
	}

	return 0;
}