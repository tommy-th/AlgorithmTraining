#include <stdio.h>

int main(){
	
	int x,y,n, star=1, count=1;

	scanf("%d", &n);

	while (star < n){
		n -= star;
		star += 2;
		count++;
	}

	if (count % 2 == 1){
		if (n > count){
			x = 2 * count - n;
			y = count;
		}
		else{
			x = count;
			y = n;
		}
	}
	else{
		if (n > count){
			x = count;
			y = 2*count -n;
		}
		else{
			x = n;
			y = count;
		}
	}
	printf("%d %d", x, y);
}
