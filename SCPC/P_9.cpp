#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;


const int alen[3] = { 0, 14, 100 };
char atoms[3][200][5] = { {}, {"","h", "b", "c", "n", "o", "f", "p", "s", "k", "v", "y", "i", "w", "u"}, \
						{"","he","li","be","ne","na","mg","al","si","cl","ar","ca","sc","ti","cr","mn",\
						 "fe","co","ni","cu","zn","ga","ge","as","se","br","kr","rb","sr","zr","nb",\
						 "mo","tc","ru","rh","pd","ag","cd","in","sn","sb","te","xe","cs","ba","hf",\
						 "ta","re","os","ir","pt","au","hg","tl","pb","bi","po","at","rn","fr","ra",\
						 "rf","db","sg","bh","hs","mt","ds","rg","cn","fl","lv","la","ce","pr","nd",\
						 "pm","sm","eu","gd","tb","dy","ho","er","tm","yb","lu","ac","th","pa","np",\
						 "pu","am","cm","bk","cf","es","fm","md", "no", "lr"} };

int T, N, D[50005];
char input[50005]; 

int compare(int n, int idx){
	int ret = 0;
	for (int i = 1; i <= alen[idx]; i++){
		if (strncmp(&input[n - idx + 1], atoms[idx][i], idx) == 0) ret = 1;
	}
	return ret;
}

void isTrue(){
	D[0] = 1;
	for (int i = 1; i <= N; i++){
		if (D[i - 1] && compare(i, 1)) D[i] = 1;
		if (i != 1){
			if (D[i - 2] && compare(i, 2)) D[i] = 1;
		}
	}
	if (D[N]) cout << "YES" << endl;
	else cout << "NO" << endl;
}

int main(){

	cin >> T;
	for (int t = 1; t <= T; t++){
		memset(D, 0, sizeof(D));
		cin >> &input[1];
		N = strlen(&input[1]);

		printf("Case #%d\n", t); 
		isTrue();
	}

	return 0;
}