#include <stdio.h>

int pol[4][32]; 
int idx[4]; 

int move(int num, int cur, int c_num, int tar, int sub){
	int count = 0, i = 1;
	
	if (pol[cur][c_num + 1] != 0) count += move(pol[cur][c_num + 1], cur, c_num + 1, sub, tar);

	while (pol[tar][i] > num) i++;

	if (pol[tar][i] != 0) count += move(pol[tar][i], tar, i, sub, cur);

	if (pol[cur][c_num + 1] != 0) count += move(pol[cur][c_num + 1], cur, c_num + 1, sub, tar);
	
	pol[tar][i] = num;
	idx[tar]++;
	pol[cur][c_num] = 0;
	idx[cur]--;

	return count + 1;
}

int main(){

	int n, i, j, k, mj, temp, result = 0, on = 0;

	// 입력부
	scanf("%d", &n);
	scanf("%d %d %d", &idx[1], &idx[2], &idx[3]);
	for (i = 1; i <= idx[1]; i++) scanf("%d", &pol[1][i]);
	for (i = 1; i <= idx[2]; i++) scanf("%d", &pol[2][i]);
	for (i = 1; i <= idx[3]; i++) scanf("%d", &pol[3][i]);
	
	//설정
	for (i = 1; i < 4; i++){
		if (pol[i][1] == n) mj = i;
	}

	// 실행부
	temp = n - 1; k = 2;
	while (temp != 0){
		if (pol[mj][k] != temp){
			for (i = 1; i < 4; i++){
				for (j = 1; j <= idx[i]; j++){
					if (pol[i][j] == temp){
						result += move(temp, i, j, mj, 6 - i - mj);
						on = 1; 
					}
					if (on) break;
				}
				if (on) break;
			}
		}
		on = 0;
		temp--;
		k++;
	}

	printf("%d\n%d", mj, result);

	return 0;
}