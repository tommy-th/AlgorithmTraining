#include <stdio.h>

int main(){

	int i,j, d, r, u = 1, idx = 0;
	int s[17000] = { 0, };

	scanf("%d %d", &d, &r);

	while (u <= d){
		u *= r;
		idx++;
	}
	j = idx--;
	u /= r;

	while (idx > 0){
		s[idx] = (d / u);
		d -= (d / u)*u;
		idx--;
		u /= r;
	}
	s[0] = d;

	for (i = j; i >= 0; i--){
		if (s[i] >= 10){
			printf("%c", s[i] + 55);
		}
		else{
			if (i == j){}
			else
				printf("%d", s[i]);
		}
	}

	return 0;
}