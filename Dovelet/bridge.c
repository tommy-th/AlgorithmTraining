#include <stdio.h>
#include <string.h>

static char answer[21];
static char angel[101];
static char devile[101];
static int ans_len;
static int bri_len;
static int sum;
static int D[21][101][2];

// i = ans의 위치 / j = bri의 위치 / t = y축 위치 
int serch(int i, int j, int t){
	int temp = 0;
	int idx = j + 1;
	if (i == ans_len - 1) return 1;
	else{
		if (t == 1){
			while (idx != bri_len){
				if (answer[i + 1] == angel[idx]){
					if (D[i + 1][idx][0] == 0) D[i + 1][idx][0] = serch(i + 1, idx, 0);
					temp += D[i + 1][idx][0];
				}
				idx++;
			}
		}
		else{
			while (idx != bri_len){
				if (answer[i + 1] == devile[idx]){
					if (D[i + 1][idx][1] == 0) D[i + 1][idx][1] = serch(i + 1, idx, 1);
					temp += D[i + 1][idx][1];
				}
				idx++;
			}
		}
	}
	return temp;
}

int main(){

	int c, i, j;

	scanf("%d", &c);
	scanf("%s", answer);
	scanf("%s", angel);
	scanf("%s", devile);
	bri_len = strlen(angel);
	ans_len = strlen(answer);

	for (j = 0; j < bri_len; j++){
		if (angel[j] == answer[0])
			sum += serch(0, j, 0);
		if (devile[j] == answer[0])
			sum += serch(0, j, 1);
	}

	printf("%d\n", sum);

	return 0;
}