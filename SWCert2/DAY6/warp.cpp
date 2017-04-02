#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>

#define DEBUG

using namespace std;

typedef long long INT64;
const int MAX_N = 100000;
const int MAX_M = 500000;
const INT64 MAX_C = 1000000000000ll;

typedef struct EDGE {
	int e;
	INT64 w;
};

typedef struct NODE {
	int from;
	INT64 dist;
	vector<EDGE> edges;	
};

int V, E;
NODE nodes[MAX_N+9];
int visited[MAX_N+9];
int topological_sort_orders[MAX_N+9];
int TPOS;

void DFS(int s)
{
	visited[s] = 1;
	
	for (int i = 0; i < nodes[s].edges.size(); ++i) {
		EDGE& e = nodes[s].edges[i];
		
		if (! visited[e.e]) {
			DFS(e.e);
		}
	}
	topological_sort_orders[TPOS--] = s;
}

void DFS_all()
{
	memset(visited, 0, sizeof(visited));
	
	TPOS = V;
	for (int i = 1; i <= V; ++i) {
		if (! visited[i])
			DFS(i);
	}
}

INT64 WARP()
{
	DFS_all();
#ifdef DEBUG
	printf("topological sort order: ");
	for (int i = 1; i <= V; ++i) {
		printf("%d ", topological_sort_orders[i]);
	}
	printf("\n");
#endif

	nodes[topological_sort_orders[1]].dist = 0ll;
	nodes[topological_sort_orders[1]].from = topological_sort_orders[1];

	for (int i = 1; i <= V; ++i) {
		NODE& here = nodes[topological_sort_orders[i]];
		
		for (int j = 0; j < here.edges.size(); ++j) {
			EDGE& edge = here.edges[j];
			INT64 nCost = here.dist + edge.w;
#ifdef DEBUG
			printf("%d : -> %d (prev= %lld, new= %lld)\n", topological_sort_orders[i], edge.e,  nodes[edge.e].dist, nCost);
#endif
			if (nCost < nodes[edge.e].dist) {
				/* Relax */
				nodes[edge.e].dist = nCost;
			}
		}
	}
	
	return nodes[V].dist;
}

int main()
{
#ifdef DEBUG
	freopen("C:\\temp\\warp.txt", "r", stdin);
	freopen("C:\\temp\\result.txt", "w", stdout);
#endif	
	scanf("%d %d", &V, &E);	
	
	int a, b;
	INT64 c;
	for (int i = 1; i <= E; ++i) {
		scanf("%d %d %lld", &a, &b, &c);
		
		EDGE e;
		e.e = b; e.w = c;
		nodes[a].edges.push_back(e);
	}
	
	for (int i = 1; i <= V; ++i)
		nodes[i].dist = MAX_C;
	
	INT64 result = WARP();
	if (result != MAX_C)
		printf("%lld\n", result);
	else 
		printf("-1\n");
	return 0;
}

