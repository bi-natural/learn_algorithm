
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

const int MAX_N = 20000;
const int MAX_E = 100000;

int V, E, S;

NODE nodes[MAX_N+9];
int visited[MAX_N+9];

vector<int> traverse;

void DFS(int s)
{
	visited[s] = 1;

	traverse.push_back(s);	
	for (int i = 0; i < nodes[s].edges.size(); ++i) {
		int nodei = nodes[s].edges[i];
		
		if (! visited[nodei]) {
			DFS(nodei);
		}
	}
}

void BFS(int s)
{
	queue<int> q;
	
	q.push(s);
	visited[s] = 1;
	while (! q.empty()) {
		int nodei = q.front(); q.pop();
		
		traverse.push_back(nodei);
		for (int i = 0; i < nodes[nodei].edges.size(); ++i) {
			int nexti = nodes[nodei].edges[i];
			if (! visited[nexti]) {
				visited[nexti] = 1;
				q.push(nexti);
			}
		}
	}
}

int main()
{

#ifdef DEBUG
	freopen("C:\\temp\\graph.txt", "r", stdin);
	freopen("C:\\temp\\result.txt", "w", stdout);
#endif	
	scanf("%d %d %d", &V, &E, &S);	
	
	for (int i = 1, a, b; i <= E; ++i) {
		scanf("%d %d", &a, &b);
		
		nodes[a].edges.push_back(b);
		nodes[b].edges.push_back(a);
	}
	
	for (int i = 1; i <= V; ++i) {
		sort(nodes[i].edges.begin(), nodes[i].edges.end());	
	}
	
#ifdef DEBUG
	for (int i = 1; i <= V; ++i) {
		printf("%d : ", i);
		for (int j = 0; j < nodes[i].edges.size(); ++j) 
			printf("%d ", nodes[i].edges[j]);
		printf("\n");
	}
#endif

	memset(visited, 0, sizeof(visited));
	DFS(S);
	for (int i = 0; i < traverse.size(); ++i)
		printf("%d ", traverse[i]);
	printf("\n");
	
	memset(visited, 0, sizeof(visited));
	traverse.clear();
	BFS(S);
	for (int i = 0; i < traverse.size(); ++i)
		printf("%d ", traverse[i]);
	printf("\n");
	return 0;
}
