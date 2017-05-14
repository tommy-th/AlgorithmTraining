/*
	문제: Dovelet 21단계 tourist
	날짜: 2015-10-22
	실행시간: 1.41s
*/
#include <iostream>
using namespace std;

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

typedef struct __point{
	int y, x;
	__point(){ y = x = 0; }
	__point(int y, int x) : y(y), x(x){}
} POINT;

const int dir[4][4] = { {-1,0,-1,0}, {-1,0,0,-1}, {0,-1,-1,0}, {0,-1,0,-1} };
int map[105][105], D[105][105][105][105];
int W, H;
POINT red, blue;

bool onField(POINT p){
	if (p.x<1 || p.x>W) return false;
	if (p.y<1 || p.y>H) return false;
	return true;
}

bool onRoad(POINT p){
	if (map[p.y][p.x] < 0) return false;
	else return true;
}

void setPoint(POINT* p, int y, int x){ 
	(*p).x = x;
	(*p).y = y;
}

void movePoint(POINT* p){
	(*p).x--, (*p).y++;
}

int curMaxStars(){
	int ret = 0;
	if (map[red.y][red.x]) ret++;
	if (map[blue.y][blue.x]) ret++;
	if (red.y == blue.y && red.x == blue.x && map[red.y][red.x]) ret--;
	return ret;
}

int prevMaxStars(){
	int temp, ret = 0;

	for (int i = 0; i < 4; i++){
		temp = D[red.y + dir[i][0]][red.x + dir[i][1]][blue.y + dir[i][2]][blue.x + dir[i][3]];
		ret = MAX(temp, ret);
	}
	return ret;
}

void setDiagonalTable(int sy, int sx){
	setPoint(&red, sy, sx);

	while (onField(red)){
		setPoint(&blue, red.y, red.x);
		while (onField(blue) && onRoad(red)){
			if (onRoad(blue))
				D[red.y][red.x][blue.y][blue.x] = prevMaxStars() + curMaxStars();
			movePoint(&blue);
		}
		movePoint(&red);
	}
}

int finalMaxPoints(){
	for (int j = 1; j <= W; j++) setDiagonalTable(1, j);
	for (int i = 2; i <= H; i++) setDiagonalTable(i, W);
	return D[H][W][H][W];
}

int main(){

	char input[105];

	cin >> W >> H;
	for (int i = 1; i <= H; i++){
		cin >> &input[1];
		for (int j = 1; j <= W; j++){
			if (input[j] == '*') map[i][j] = 1;
			else if (input[j] == '#') map[i][j] = -1;
		}
	}
	cout << finalMaxPoints() << endl;

	return 0;
}