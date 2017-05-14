#include <stdio.h>

int main(){

	int k, i,j[6];
	int s[13];

	scanf("%d", &k);

	for (i = 0; i < k; i++)
		scanf("%d", &s[i]);

	for (j[0] = 0; j[0] < k - 5; j[0]++){
		for (j[1] = j[0]+1; j[1] < k - 4; j[1]++){
			for (j[2] = j[1]+1; j[2] < k - 3; j[2]++){
				for (j[3] = j[2]+1; j[3] < k - 2; j[3]++){
					for (j[4] = j[3]+1; j[4] < k - 1; j[4]++){
						for (j[5] = j[4]+1; j[5] < k; j[5]++){
							printf("%d %d %d %d %d %d\n", s[j[0]], s[j[1]], s[j[2]], s[j[3]], s[j[4]], s[j[5]]);
						}
					}
				}
			}
		}
	}

}