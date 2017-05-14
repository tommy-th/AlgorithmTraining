#include <stdio.h>

char S[200001];
char buf[201][11];
int k;

int main(){

	char sub[11];
	int i = 0;
	
	do{
		scanf("%s", buf[k]);
	} while (strcmp(buf[k++] , "."));
	getchar();
	gets(S);

	strncpy(sub, S, strlen(buf[0]));
	sub[strlen(buf[0])] = '\0';

	printf("%d\n", i);

	return 0;
}