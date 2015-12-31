#include <stdio.h>
#include <stdlib.h>

static int N;
static int E;
static int num[101];
static int D[101][101];

typedef struct __stack{
	int top;
	int capacity;
	int* data;
}stack;

stack* init_stack(){
	stack* temp = (stack*)malloc(sizeof(stack));
	temp->capacity = 1;
	temp->data = (int*)malloc(sizeof(int)*temp->capacity);
	temp->top = 0;
	return temp;
}

int full_stack(stack* s){
	return (s->top == s->capacity);
}

int empty_stack(stack* s){
	return (s->top == 0);
}

void push(stack* s, int data){
	if (full_stack(s)){
		s->capacity *= 2;
		s->data = (int*)realloc(s->data, s->capacity*sizeof(int));
	}
	s->data[s->top] = data;
	s->top++;
}

int pop(stack* s){
	int temp = s->data[s->top - 1];
	if (empty_stack(s)) return 0;
	s->top--;
	return temp;
}

void delete_stack(stack* s){
	if (s){
		if (s->data){
			free(s->data);
		}
		free(s);
	}
}

void print_stack(stack* s, int n);

void path(stack* s, int n){
	int i=1;
	while (D[n][i] == 0 && i <= N){ i++; }
	if (D[n][i] == 1){
		D[n][i] = 0;
		D[i][n] = 0;
		push(s, i);
		path(s, i);
	}
	else{
		printf("%d ", pop(s));
		if (empty_stack(s)) return;
		else path(s, s->data[s->top - 1]);
	}
}

int main(){

	stack* s = init_stack();
	int i, j, a, b, start = 0, fal = 0;

	scanf("%d %d", &N, &E);

	for (i = 1; i < E + 1; i++){
		scanf("%d %d", &a, &b);
		D[a][b] = 1;
		D[b][a] = 1;
		num[a]++;
		num[b]++;
	}

	for (i = 1; i < N; i++){
		if (num[i] % 2 == 1){
			start = i;
			fal++;
		}
		else if (start == 0){
			start = i;
		}
	}

	if (fal>2){
		printf("0\n");
		return 0;
	}	
	push(s, start);
	path(s, start);
	delete_stack(s);

	return 0;
}
