/*
 * 피크닉
 * 
 --
소들은 피크닉을 갈 예정이다! 각 존의 K(1≤K≤100)마리의 소들은 
N(1≤N≤1000) 개의 목초지중 하나의 목초지에서 풀을 뜯고 있다. 이 목초지들을 목초지 
1,2,?,N이라고 명명하자.

그 목초지들은 M(1≤M≤10000) 개의 단방향 길로 연결되어 있다. (어떠한 길도 출발지와 도착지가 같지 않다.)

소들은 그들의 피크닉동안 같은 목초지에서 모이기를 원한다. 하지만 몇마리의 소들은 모든 목초지에 
도달할 수 없을 가능성이 있다.(단방향 도로이기 때문에) 소들을 도와 얼마나 많은 목초지에서 모든 
소들이 모일 수 있는지 계산해주자.
 --
 
 도달가능한 것을 찾기 위해 DFS를 사용한다. 
 소의 위치에서 DFS 탐색을 하면서 탐색된 노드에 +1를 추가한다.
 모든 소들의 탐색이 끝난 후에 노드의 카운트값이 소들의 개수만큼 있는 곳들이 답이다. 
 */
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

const int MAX_K = 100;
const int MAX_N = 1000;
const int MAX_M = 10000;

struct TREE {
	int parent;
	vector<int> childen;
};

int K, N, M;

int KLOC[MAX_K+9];
TREE tree[MAX_N+9];
int visited[MAX_N+9];
int visit_count[MAX_N+9];

void dfs(int n)
{
	visited[n] = 1;
	for (int i = 0; i < tree[n].childen.size(); ++i) {
		if (! visited[tree[n].childen[i]]) 
			dfs(tree[n].childen[i]);
	}
	visit_count[n] ++;
}

vector<int> PICNIC()
{
	memset(visit_count, 0, sizeof(visit_count));
	
	for (int i = 1; i <= K; ++i) {
		memset(visited, 0, sizeof(visited));
		dfs(KLOC[i]);
		
#ifdef DEBUG
	printf("after %d : ", i);
	for (int i = 1; i <= N; ++i) 
		printf("%d ", visit_count[i]);
	printf("\n");
#endif		
	}
	
	vector<int> result;
	
	for (int i = 1; i <= N; ++i) {
		if (visit_count[i] == K) 
			result.push_back(i);
	}
	return result;
}

int main()
{
#ifdef DEBUG
	freopen("C:\\temp\\picnic.txt", "r", stdin);
	freopen("C:\\temp\\result.txt", "w", stdout);
#endif	
	scanf("%d %d %d", &K, &N, &M);

	for (int i = 1; i <= K; ++i) 
		scanf("%d\n", KLOC + i);
		
	for (int i = 1, a, b; i <= M; ++i) {
		scanf("%d %d", &a, &b);
		tree[a].childen.push_back(b);
	}
	
	vector<int> result = PICNIC();	
	printf("%d\n", result.size());
	return 0;
}
