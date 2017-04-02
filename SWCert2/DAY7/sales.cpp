#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>

#define DEBUG
#define MAX_N 100007

using namespace std;

typedef long long INT64;

int N;

struct NODE  {
	vector<int> edges;
};

NODE nodes[MAX_N];
int parent[MAX_N][20];
int depth[MAX_N];

void makeTable(int dep, int s)
{
	memset(depth, -1, sizeof(depth));
	memset(parent, 0, sizeof(parent));

	queue<int> q;
	
	parent[s][0] = s;	/* 자기 자신 */ 
	depth[s] = dep;
	q.push(s);
	while(!q.empty()) {
		int t = q.front(); q.pop();
		
		for (int i = 0; i < nodes[t].edges.size(); ++i) {
			int n = nodes[t].edges[i];
			if (depth[n] == -1)	{
				depth[n] = 1 + depth[t];
				parent[n][0] = t;
				q.push(n);
			}
		}
	}
	
	/* build parent */
	for (int k = 1; k < 20; ++k)
		for (int i = 1; i <= N; ++i)
			parent[i][k] = parent[parent[i][k-1]][k-1];
			
#ifdef DEBUG
	printf("Depth:\n");
	for (int i = 1; i <= N; ++i) {
		printf("%3d ", depth[i]);
	}
	printf("\n");
	
	printf("Parent:\n");
	for (int i = 0; i <= 5; ++i) {
		printf("%d : ", i);
		for (int j = 1; j <= N; ++j) {
			printf("%3d ", parent[j][i]);
		}
		printf("\n");
	}
	printf("\n");
#endif			
}

int PATH(int a, int b)
{
	int traverse = 0, c;
	
	if (depth[a] < depth[b]) swap(a, b);

#ifdef DEBUG
	printf(" -- depth[%d] = %d, depth[%d] = %d\n", a, depth[a], b, depth[b]);
#endif
	traverse = depth[a]	 - depth[b];
	for (int i = 0; i < 20; ++i)
		if ((1 << i) & (depth[a] - depth[b])) {
			a = parent[a][i];
		}
			
	if (a == b) return traverse;
	
	c = a;
	for (int i = 20; i-- > 0; )
		if (parent[a][i] != parent[b][i]) {
			a = parent[a][i], b = parent[b][i];
		}
			
#ifdef DEBUG
	printf(" -- traverse += (a = %d -> %d)\n", c, a, depth[c], depth[a]);
#endif			
	return traverse + 2 * (depth[c] - depth[parent[a][0]]);
}

INT64 LCA()
{
	makeTable(0, 1);
	
	INT64 path = 0ll;
	for (int i = 1; i < N; ++i) {
		path += (INT64) (PATH(i, i+1));
	}
	return path;
}

int main()
{
#ifdef DEBUG
	freopen("C:\\temp\\sales.txt", "r", stdin);
	freopen("C:\\temp\\result.txt", "w", stdout);
#endif	
	scanf("%d", &N);
	for (int i = 1, a, b; i <= N-1; ++i ){		
		scanf("%d %d", &a, &b);
		nodes[a].edges.push_back(b);
		nodes[b].edges.push_back(a);
	}
	
	INT64 result = LCA();
	printf("%lld\n", result);
	return 0;
}
