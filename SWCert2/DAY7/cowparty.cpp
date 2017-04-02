#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>

#define DEBUG

using namespace std;

typedef long long INT64;
typedef pair<int, int> BOX;

const int MAX_V = 1000;

struct NODE {
	vector<BOX> edges;
};

void Bellman(int s, int e)
{
	
}

int D[MAX_V+9][MAX_V+9];

int V, E, K;

NODE nodes[MAX_V+9];
NODE nodes_R[MAX_V+9];

int DIST[MAX_V+9][MAX_V+9];

int edges[MAX_V+9][MAX_V+9];
int ROUND[MAX_V+9];

struct cmp_MINHEAP {
	/* first  == distance
	 * second == node
	 */
	bool operator()(const BOX& lhs, BOX& rhs) {
		return lhs.first > rhs.first;
	}
};

void DIJKSTRA(NODE nodes[], int s, int e)
{
	priority_queue<BOX, vector<BOX>, cmp_MINHEAP> pq;
	
	for (int i = 1; i <= V; ++i)
		DIST[s][i] = 10000000;
		
	DIST[s][s] = 0;
	pq.push(BOX(0, s));
	while (!pq.empty()) {
		BOX top = pq.top(); pq.pop();
		
		NODE& here = nodes[top.second];
		
		if (DIST[s][top.second] != top.first)
			continue;
			
		for (int i = 0; i < here.edges.size(); ++i) {
			BOX& there = here.edges[i];
			
			if (DIST[s][there.first] > top.first + there.second) {
				DIST[s][there.first] = top.first + there.second;
				pq.push(BOX(DIST[s][there.first], there.first));
			} 
		}
	}
#ifdef DEBUG
	printf("Dijkstra(%d) = ", s);
	for (int i = 1; i <= V; ++i)
		printf("%3d ", DIST[s][i]);
	printf("\n");
#endif
}

int COW_PARTY2()
{
#ifdef DEBUG
	for (int i = 1; i <= V; ++i) {
		printf(" node %d : ", i);
		for (int j = 0; j < nodes[i].edges.size(); ++j) {
			printf("%d ", nodes[i].edges[j]);
		}
		printf("\n");
	}
	
#endif
	for (int i = 1; i <= V; ++i) {
		DIJKSTRA(nodes, i, K);
	}
	
	/* All node ---> K ----> All node */
	int findMax = 0;
	for (int i = 1; i <= V; ++i) {
		ROUND[i] = DIST[i][K] + DIST[K][i];
		findMax = max(ROUND[i], findMax);
	}
			
	return findMax;	
}

int COW_PARTY3()
{
	DIJKSTRA(nodes, K);
	DIJKSTRA(nodes_R, K);
}

int COW_PARTY()
{
	memset(D, -1, sizeof(D));
	
	/* init value */
	for (int i = 1;  i <= V; ++i)
		for (int j = 1; j <= V; ++j) {
			if (i == j)
				D[i][j] = 0ll;
			else if (edges[i][j])
				D[i][j] = edges[i][j];
			else
				D[i][j] = 100000000000ll;
		}

	/* run Floyd Warshall */
	for (int k = 1; k <= V; ++k) {
		for (int i = 1; i <= V; ++i) 
			for (int j = 1; j <= V; ++j) {
				// if (D[i][k] != -1ll && D[k][j] != -1ll) 
				{					
					D[i][j] = min(D[i][j], D[i][k] + D[k][j]);
#ifdef DEBUG
					printf("iteration(%d) %d %d\n", k, i, j);
					for (int ii = 1; ii <= V; ++ii) {
						for (int jj = 1; jj <= V; ++jj) {
							printf("%3d ", D[ii][jj]);
						}
						printf("\n");
					}
#endif
				}

			}
	}
	
	/* All node ---> K ----> All node */
	int findMax = 0;
	for (int i = 1; i <= V; ++i) {
		ROUND[i] = D[i][K] + D[K][i];
		findMax = max(ROUND[i], findMax);
	}
			
	return findMax;

}

int main()
{
#ifdef DEBUG
	freopen("C:\\temp\\cowparty.txt", "r", stdin);
	freopen("C:\\temp\\result.txt", "w", stdout);
#endif	
	scanf("%d %d %d", &V, &E, &K);	
	
	memset(edges, 0, sizeof(edges));
	for (int i = 1, a, b, c; i <= E; ++i) {
		scanf("%d %d %d", &a, &b, &c);
		edges[a][b] = c;
		
		/* for Dijkstra */
		nodes[a].edges.push_back(BOX(b, c));
		nodes_R[b].edges.push_back(BOX(a, c));
	}
	
	int result = COW_PARTY3();
	printf("%d\n", result);
	return 0;
}
