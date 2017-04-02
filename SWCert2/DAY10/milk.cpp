/*
 * 우유의 최대양 구하기  
 *
 --
 농부 존은 그의 곳간에 있는 N개의 외양간 사이에 우유를 옮기기 위해 
N?1개의 파이프를 설치했다. (2≤N≤50,000). 편의를 위해 각 외양간을 1...N이라고 하자. 
각 파이프는 두 개의 외양간을 연결하고, 모든 외양간은 파이프들로 서로 연결되어 있다.

존은 K쌍의 외양간 사이에서 펌프로 우유를 주고받고 있다 (1≤K≤100,000). 
i번째 길의 양 끝 외양간 si와 ti가 주어진다. 이 길을 통해 우유가 한 단위씩 오간다. 
존은 몇 외양간에서 오가는 우유의 양을 감당하지 못 할 것이 걱정된다. 왜냐하면 어떤 외양간이 여러 
K길들이 거쳐가는 지점이 될 수도 있기 때문이다. 어떤 외양간을 지나가는 우유 양의 최댓값을 구하라. 

만약 우유가 si와 ti가 연결된 길로 오간다면, 외양간 si와 ti, 그리고 
그 길이 통과하는 여러 외양간들에 우유가 통과한다고 생각하면 된다.
 -- 
 * 
 */
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>

#define DEBUG
#define MAX_N         50007
#define MAX_Q		1000007

using namespace std;

typedef long long INT64;
typedef pair<int, int> PPI;

int CASE; 
int N, K; 

struct NODE  {
	int jobs;
	int milk;
	vector<int> edges;
};

struct QUERY {
	int s, t;	
};

NODE  nodes[MAX_N];
QUERY querys[MAX_Q];
int   VNODE_jobs;

int parent[MAX_N][20];
int depth[MAX_N];

/*
 * Build LCA Table
 *
 * input parameters : start node (s)
 *
 * output 
 *     parent[i] - i노드의 parent history maps 
 *     depth[i]  - i노드의 depth
 * 
 * 시간공간복잡도 : O(n log n) 
 */
void buildLCATable(int s)
{
	memset(depth, -1, sizeof(depth));
	memset(parent, 0, sizeof(parent));

	/* build depth + first ancestor(direct parent) using BFS */
	queue<int> q;
	
	parent[s][0] = s;	/* 자기 자신 */ 
	depth[s] = 0;		/* 깊이는 0에서 시작 */ 
	q.push(s);
	while(!q.empty()) {
		int here = q.front(); q.pop();
		
		for (int i = 0; i < nodes[here].edges.size(); ++i) {
			int n = nodes[here].edges[i];
			
			if (depth[n] == -1)	{				/* not visited */
				depth[n] = 1 + depth[here];		/* here + 1 증가 */ 
				parent[n][0] = here;			/* 첫번째 ancestor는 parent */ 
				q.push(n);
			}
		}
	}
	
	/* build ancestors... */
	
	/*
	 * k = 0 : 2^0 = parent
	 * k = 1 : 2^1 = ancestor 2 upside 
	 * k = 2 : 2^2 = ancestor 4 upside
	 * k = 3 : 2^3 = ancestor 8 upside
	 *  :
	 * k = 20 : 2^20 = ancestor 2^20 upside
	 *
	 */
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

/*
 * findLCA 
 *
 * input parameters
 *    a , b : 임의의 노드
 *
 * output
 *    a, b의 최저공통조상 (정의: a, b의 조상들중에 가장 먼저 만나는 조상) 
 */
int findLCA(int a, int b)
{
#ifdef DEBUG11
    printf("+ findLca(%d, %d)\n", a, b);
	printf("  - depth[%d] = %d, depth[%d] = %d\n", a, depth[a], b, depth[b]);
	printf("  - parent[%d] = %d, parent[%d] = %d\n", a, parent[a][0], b, parent[b][0]);
#endif
	/* 
	 * step1: depth를 동일하게 맞춘다.
	 */ 	 
	if (depth[a] < depth[b]) swap(a, b);   /* a가 더 크도록 맞춘다. */ 

	/* a의 depth가 같아지도록 a의 ancestor까지 위로 올린다. */ 
	for (int i = 0; i < 20; ++i)
		if (((1 << i) & (depth[a] - depth[b])) != 0) {
			a = parent[a][i];
		}
	
	/* 동일한 depth에서 a = b의 두 parent가 같다면 이미 찾은 것임 
	 * 그외에 경우에 대해서 찾는다. 
	 */ 
	if (a != b) {
		/*
		 * step2: 맨 꼭대기부터 최소 공통조상까지 내려온다.  
		 */
		for (int i = 19; i >= 0; --i) 
			if (parent[a][i] != parent[b][i]) {
				a = parent[a][i];
				b = parent[b][i];
			}		
			
		a = parent[a][0]; 
	}
	
#ifdef DEBUG11
	printf(" -> %d\n", a);
#endif
	return a;
}

int visited[MAX_N];

int milk_update(int s)
{
	visited[s] = 1;
	
	nodes[s].milk = nodes[s].jobs;
	
	for (int i = 0; i < nodes[s].edges.size(); ++i) {
		if (! visited[nodes[s].edges[i]]) {
			nodes[s].milk += milk_update(nodes[s].edges[i]);
		}
	}
	
	return nodes[s].milk;
}

int MILK()
{
	buildLCATable(1);
	
	for (int i = 1; i <= K; ++i ) { 
		int s = querys[i].s;
		int t = querys[i].t;
		int lca = findLCA(s, t);
		
		if (lca == s) {
			/* t부터 s(lca)의 parent까지 +1, -1를 추가한다. */
			nodes[t].jobs ++;
			nodes[(lca == 1) ? 0 : parent[lca][0]].jobs --;	
		} else if (lca == t) {
			nodes[s].jobs ++;
			nodes[(lca == 1) ? 0 : parent[lca][0]].jobs --;	
		} else {
			/* s, lca(s,t)의 Parent 에 +1, -1를 추가한다. */ 
			nodes[s].jobs ++;
			nodes[(lca == 1) ? 0 : parent[lca][0]].jobs --;
			
			/* t, lca(s,t)에 +1, -1를 추가한다. */ 
			nodes[t].jobs ++;
			nodes[lca].jobs --;			
		}

#ifdef DEBUG
	printf("Job Status: add (%d, %d) = lca(%d)\n", querys[i].s, querys[i].t, lca);
	for (int i = 0; i <= N; ++i) printf("%3d", i);
	printf("\n");
	for (int i = 0; i <= N; ++i) printf("%3d", nodes[i].jobs);
	printf("\n");
#endif
		
	}
	
	memset(visited, 0, sizeof(visited));	
	int milk = milk_update(1);
	
#ifdef DEBUG
	printf("Milk n");
	for (int i = 0; i <= N; ++i) printf("%3d", i);
	printf("\n");
	for (int i = 0; i <= N; ++i) printf("%3d", nodes[i].milk);
	printf("\n");
#endif
	for (int i = 0; i <= N; ++i) milk = max(milk, nodes[i].milk);
	return milk;
}

int main()
{
#ifdef DEBUG
	freopen("input\\milk.txt", "r", stdin);
	freopen("input\\result.txt", "w", stdout);
#endif	

	scanf("%d %d", &N, &K);
	
	for (int i = 1, a, b; i <= N-1; ++i ){		
		scanf("%d %d", &a, &b);
		nodes[a].edges.push_back(b);
		nodes[b].edges.push_back(a);
	}
		
	for (int i = 1, a, b; i <= K; ++i) {
		scanf("%d %d", &a, &b);
		querys[i].s = a;
		querys[i].t = b;
	}

	int result = MILK();
	
	printf("%d\n", result);
	return 0;
}

