#include <algorithm>
#include <string>
#include <vector>
#include <map>
#include <queue>
#include <set>
using namespace std;

#define SZ(V) ((int)((V).size()))
#include <math.h>
#include <stdio.h>

const int MAX_V = 8005;
const int source = 0;
const int sink = 1;
const int MAX_BUF = 11 * 1000 + 10;
char str[MAX_BUF];
map<string, int> nmap;
vector< vector<int> > data;

vector<int> eu[MAX_V];
vector<int> ec[MAX_V];
vector<int> er[MAX_V];
int V;

int getV(string s) {
	if (nmap.find(s) == nmap.end()) {
		nmap[s] = V;
		V += 2;
	}

	return nmap[s];
}
const int INF = 99999999;

void addEdge(int u, int v, int w) {
	er[u].push_back(SZ(eu[v])); //reverse index
	er[v].push_back(SZ(eu[u])); //reverse index

	eu[u].push_back(v);
	ec[u].push_back(w);

	eu[v].push_back(u);
	ec[v].push_back(0);
}

int bfs[MAX_V], bh;
int depth[MAX_V];
void bfsfill() {
	memset(depth, 0, sizeof(depth));
	bfs[0] = source;
	bh = 1;
	depth[source] = 1;

	for (int i = 0; i < bh; i++) {
		int v = bfs[i];
		for (int c = 0; c < SZ(eu[v]); c++) {
			int u = eu[v][c];
			int g = ec[v][c];

			if (g > 0) {
				if (depth[u] == 0) {
					bfs[bh] = u;
					bh++;
					depth[u] = depth[v] + 1;
				}
			}
		}
	}
}

bool chk[MAX_V];
bool dfsflow(int v) {
	if (v == sink) return true;
	chk[v] = true;
	for (int t = 0; t < SZ(eu[v]); t++) {
		int u = eu[v][t];
		int c = ec[v][t];

		if (c > 0 && !chk[u]) {
			if (dfsflow(u)) {
				int r = er[v][t];

				ec[v][t] --;
				ec[u][r] ++;
				return true;
			}
		}
	}
	return false;
}
int flow() {
	int sol = 0;
	while (true) {
		bfsfill();
		int tsol = sol;
		memset(chk, 0, sizeof(chk));
		while (dfsflow(source)) {
			sol++;
		}
		if (sol == tsol) return sol;
	}
}

int main(){
	freopen("C-large.in", "r", stdin);
	freopen("C-large.out_debug", "w", stdout);
	int T;
	scanf("%d", &T);
	for (int cs = 1; cs <= T; cs++) {
		for (int i = 0; i < MAX_V; i++) {
			eu[i].clear();
			ec[i].clear();
			er[i].clear();
		}
		int N;
		scanf("%d\n", &N);
		V = 2;
		nmap.clear();
		data.clear();
		for (int i = 0; i < N; i++) {
			fgets(str, MAX_BUF, stdin);
			int len = strlen(str);
			string s = "";
			vector<int> wlist;
			for (int j = 0; j <= len; j++) {
				char c = str[j];
				if ('a' <= c && c <= 'z') {
					s += c;
				}
				else {
					if (s.size() > 0) {
						int v = getV(s);
						wlist.push_back(v);
					}
					s = "";
				}
			}
			data.push_back(wlist);
		}

		for (int i = 0; i < SZ(data[0]); i++) {
			int w = data[0][i];
			addEdge(source, w, INF);
		}
		for (int i = 0; i < SZ(data[1]); i++) {
			int w = data[1][i];
			addEdge(w+1, sink, INF);
		}

		for (auto p : nmap) {
			int w = p.second;
			addEdge(w, w + 1, 1);
		}

		for (int i = 2; i < N; i++) {
			for (int j = 0; j < SZ(data[i]); j++) {
				for (int k = j + 1; k < SZ(data[i]); k++){
					int a = data[i][j];
					int b = data[i][k];

					if (a == b) continue;
					addEdge(a + 1, b, INF);
					addEdge(b + 1, a, INF);
				}
			}
		}
		printf("Case #%d: %d\n", cs, flow());
	}

	return 0;
}