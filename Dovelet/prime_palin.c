#include <stdio.h>
#include <math.h>

int paline[20000];

int prime_num[20000];

int ten(int t){
	if (t == 0) return 1;
	else if (t < 0)return -1;
	else return 10 * ten(t - 1);
}

int num_size(int n){
	int t = 0, u = 1;
	while (u - 1 < n){
		u *= 10;
		t++;
	}
	return t;
}

int inverse(int n){
	int i = 1, t, a, b, n1=n;
	t = num_size(n);

	while (i <= t){
		a = n1 / ten(t - 1) %10;
		n1 -= a*ten(t - 1);
		b = n1 % ten(i)/ten(i-1);
		n1 -= b*ten(i - 1);
		n1 += b*ten(t - 1);
		n1 += a*ten(i - 1);
		i++; t--;
	}

	return n1;
}

int is_prime(int n) {
	int i, sqr;
	sqr = (int)sqrt(n);
	if (n % 2 == 0) return 0;
	for (i = 3; i <= sqr+1; i +=2)
		if (n % i == 0) 
			return 0;
	return 1;
}

int main(){

	int a, b, c, i, front, back, idx1, idx2;
	int t, on = 0;

	scanf("%d %d", &a, &b);
	t = num_size(a); 

	// set a

	if (t % 2 == 0){

		idx1 = ten(t / 2);

		front = a / idx1;
		back = a % idx1;
		if (front < back && inverse(front) != back){
			front++;
			a -= back;
			back = inverse(front);
			a += back;
			a += idx1;
		}
		else{
			a -= back;
			back = inverse(front);
			a += back;
		}
	}
	else{
		idx1 = ten(t / 2);
		idx2 = ten(t / 2 + 1);

		front = a / idx2;
		back = a % idx1;
		c = a / idx1 % 10;
		if (front < back && inverse(front) != back){
			front++;
			a -= back;
			back = inverse(front);
			a += back;
			a += idx2;
		}
		else{
			a -= back;
			back = inverse(front);
			a += back;
		}
	}	
	//

	while (a<=b){

		if (is_prime(a))
			printf("%d\n", a);

		if (t % 2 == 0){
			idx1 = ten(t / 2 - 1);
			idx2 = ten(t / 2);

			front++;
			if (front / idx1 % 2 == 0 && front < idx1)
				front += idx1;
			{
				if (front == idx2){
					front /= 10;
					back = 1;
					c = 0;
					t++;
					a = ten(t - 1) + 1;
				}
				else{
					back = inverse(front);
					a = front*idx2 + back;
				}
			}
		}
		else{
			c++;
			idx1 = ten(t / 2 - 1);
			if (c == 10){
				c = 0;
				front++;
				if (front / idx1 % 2 == 0 && front < idx1)
					front += idx1;
				{
					if (front == ten(t / 2)){
						t++;
						a = ten(t - 1) + 1;
						if (a>100){
							t++;
							a = ten(t - 1) + 1;
						}
					}
					else{
						back = inverse(front);
						a = front*ten(t / 2 + 1) + back;
					}
				}
			}
			else{
				a += ten(t / 2);
			}
		}
	}
}