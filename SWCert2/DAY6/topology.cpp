#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>

#define DEBUG

using namespace std;

typedef struct NODE {
	vector<int> edges;	
};

const int MAX_N = 50000;
const int MAX_E = 100000;

int V, E;

NODE nodes[MAX_N+9];
int visited[MAX_N+9];

vector<int> topology;

void DFS(int s)
{
	visited[s] = 1;
	
	for (int i = 0; i < nodes[s].edges.size(); ++i) {
		int nodei = nodes[s].edges[i];
		
		if (! visited[nodei]) {
			DFS(nodei);
		}
	}
	topology.push_back(s);
}

void DFS_all()
{
	for (int i = 1; i <= V; ++i) {
		if (! visited[i])
			DFS(i);
	}
}

int main()
{
#ifdef DEBUG
	freopen("C:\\temp\\topology.txt", "r", stdin);
	freopen("C:\\temp\\result.txt", "w", stdout);
#endif	
	scanf("%d %d", &V, &E);	
	
	for (int i = 1, a, b; i <= E; ++i) {
		scanf("%d %d", &a, &b);
		
		nodes[a].edges.push_back(b);
	}
	
	memset(visited, 0, sizeof(visited));
	DFS_all();
	
	reverse(topology.begin(), topology.end());
	for (int i = 0; i < topology.size(); ++i)
		printf("%d ", topology[i]);
	printf("\n");
	return 0;
		
}
