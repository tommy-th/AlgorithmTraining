#include <stdio.h>

int N;
int pre_node[1002];
int cnt_node[1002];
int idx1 , idx2;

void init(){
	idx1 = idx2 = 1;
	cnt_node[N + 1] = pre_node[N + 1] = 0;
}

void print_tree(int node, int parent){
	// ÁÂÃø ³ëµå Å½»ö
	if (pre_node[idx1] != cnt_node[idx2]){
		idx1++;
		if (idx1 > N) return;
		print_tree(pre_node[idx1], node);
	}
	else{
		idx1++;
	}

	if (cnt_node[idx2+1] != parent){
		idx2++;
		if (idx2 > N) return;
		print_tree(pre_node[idx1], parent);
	}
	else{
		idx2++;
	}
	printf("%d ", node);
}

int main(){
	
	int i, j, t;

	scanf("%d", &t);
	for (i = 0; i < t; i++){
		scanf("%d", &N);

		for (j = 1; j <= N; j++){
			scanf("%d", &pre_node[j]);
		}
		for (j = 1; j <= N; j++){
			scanf("%d", &cnt_node[j]);
		}
		init();
		print_tree(pre_node[1], 0);
		printf("\n");
	}
	return 0;
}