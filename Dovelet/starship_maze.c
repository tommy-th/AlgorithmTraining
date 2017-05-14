#include <stdio.h>
#include <stdlib.h>

typedef struct __ROOM{
	int idx;
	int size;
	int past;
	int* connect;
}ROOM;

typedef struct __STACK{
	int top;
	int capacity;
	int* data;
}STACK;

static int N;
static ROOM room[100001];
static STACK* stack;

void init_room(ROOM* room){
	int	i;
	for (i = 1; i < N + 1; i++){
		room[i].size = 50;
		room[i].connect = (int*)malloc(sizeof(int)* room[i].size);
		room[i].idx = 1;
		room[i].past = 0;
	}
}

void connect_room(ROOM* room, int a, int b){
	if (room[a].size == room[a].idx){
		room[a].size *= 1.4;
		room[a].connect = (int*)realloc(room[a].connect, room[a].size*sizeof(int));
	}
	room[a].connect[room[a].idx++] = b;
}

void delete_room(ROOM* room){
	int	i;
	for (i = 1; i < N + 1; i++){
		free(room[i].connect);
	}
}

STACK* init_stack(){
	STACK* temp = (STACK*)malloc(sizeof(STACK));
	temp->capacity = 1;
	temp->data = (int*)malloc(sizeof(int)*temp->capacity);
	temp->top = 0;
	return temp;
}

int full_stack(STACK* s){
	return (s->top == s->capacity);
}

int empty_stack(STACK* s){
	return (s->top == 0);
}

void push(STACK* s, int data){
	if (full_stack(s)){
		s->capacity *= 2;
		s->data = (int*)realloc(s->data, s->capacity*sizeof(int));
	}
	s->data[s->top] = data;
	s->top++;
}

int pop(STACK* s){
	int temp = s->data[s->top - 1];
	if (empty_stack(s)) return 0;
	s->top--;
	return temp;
}

void delete_stack(STACK* s){
	if (s){
		if (s->data){
			free(s->data);
		}
		free(s);
	}
}

void move(int n){
	int i, j, temp = 100001;

	room[n].past = 1;
	for (i = 1; i < room[n].idx; i++){
		if (room[room[n].connect[i]].past != 1 && room[n].connect[i] < temp){
			temp = room[n].connect[i];
		}
	}

	if (temp != 100001){
		printf("%d ", temp);
		push(stack, n);
		move(temp);
	}
	else{
		if (!empty_stack(stack)) move(pop(stack));
	}
}

int main(){

	int i, j, a, b, e;

	scanf("%d %d", &N, &e);
	init_room(room);
	stack = init_stack();

	for (i = 0; i < e; i++){
		scanf("%d %d", &a, &b);
		connect_room(room, a, b);
		connect_room(room, b, a);
	}
	printf("1 ");
	move(1);
	printf("\n");

	delete_stack(stack);
	delete_room(room);

	return 0;
}