#include <stdio.h>
#include <string.h>

int main(){

	char alpa[27] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z' };
	char key[27];
	char str[81];
	int i, j, len;
	int u[81] = { 0, };

	gets(key);
	gets(str);

	len = strlen(str);

	for (i = 0; i < len+1; i++){
		if (str[i] < 97){
			str[i] += 32;
			u[i] = -1;
		}
	}

	for (i = 0; i < len+1; i++){
		for (j = 0; j < 27; j++){
			if (str[i] == alpa[j]){
				str[i] = key[j];
				j = 27;
			}
		}
		if (u[i]==-1){
			str[i] -= 32;
		}
		printf("%c", str[i]);
	}

	return 0;
}