/*
 * 웜홀
 *
 --
 그의 많은 농장들을 탐험하던중, 존은 몇 개의 놀라운 웜홀을 발견했다. 웜홀은 현재 농장에서 
 다른 농장으로의 이상한 단방향 통로로써 당신이 들어갔던 시간보다 이전시간으로 시간을 되돌린다. 
 존의 농장은 N개의 농장과 M개의 양방향 도로, W개의 웜홀로 구성되어있다. 그리고 각 농장은 편의상 
 농장1, 농장2, … ,농장 N이라고 이름붙여주자.

존은 갑자기 현재위치에서 출발해서 여행을 하다 다시 현재위치로 돌아왔을 때 시간이 되돌아 가 있는 
경우가 있는지 궁금해졌다. 존을 도와 시간을 되돌리는 여행이 가능한지 구하는 프로그램을 작성하여라
 -- 
 
 음수간선에 의해 사이클이 생기는 경우를 체크하는 것임.
 벨만포트를 사용하여 구한다음에 N+1이 지나도록 끝나지 않는지 체크. 
 
 1. 가상의 노드를 사용하여 모든 정점까지 거리가 0인 것을  추가
 2. 나머지 N개의 노드에 대해 N번의 relaxation 시도
 3. N+1에도 계속해서 relaxation이 되면 음수간선이 있음. 
  
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

#define MAX_V 509
#define MAX_E 2509
#define MAX_W 200

int CASE; 
int V, E, W;

int A[MAX_V+9][MAX_V+9];
vector<BOX> nodes[MAX_V+9];

int D[MAX_V+9];

/* bellman Ford */

bool WARP()
{
	queue<int> q2[2], *q, *nq;
	
	q = &q2[0], nq = &q2[1];
	
	/* start from Virtual Node & dist zero !! */
	for (int i = 1; i <= V; ++i) {
		/* relax all to zero, immedately */
		D[i] = 0;
		q->push(i);
	}

	bool relaxed;
	for (int iter = 1; iter <= V; ++iter) {		
		relaxed = false;
#ifdef DEBUG
		printf(" iter(%d) ", iter);
		for (int k = 1; k <= V; ++k) {
			printf("%d ", D[k]);
		}
		printf("\n");
#endif
		while (!q->empty()) {
			int here = q->front(); q->pop();
			
#ifdef DEBUG
			printf(" iter(%d) pop : %d (cost = %d)\n", iter, here, D[here]);
#endif			
			for (int j = 0; j < nodes[here].size(); ++j) {
				BOX& there = nodes[here][j];
				int cost  = D[here] + there.second;
				
				if (cost < D[there.first]) {
					/* relaxed */
					relaxed = true;
					D[there.first] = cost;
					nq->push(there.first);
#ifdef DEBUG
					printf(" iter(%d) relaxed & push : %d (cost = %d)\n", iter, there.first, cost);
#endif	
				}
			}			
		}

		if (relaxed && iter == V) 
			return true;
		
		swap(q, nq);
	}
	
	return false;
}

int main()
{
#ifdef DEBUG
	freopen("C:\\temp\\warmhole.txt", "r", stdin);
	freopen("C:\\temp\\result.txt", "w", stdout);
#endif

	scanf("%d", &CASE);
	for (int t = 1; t <= CASE; ++t) {
		scanf("%d %d %d", &V, &E, &W);	
		
		for (int i = 1; i <= V; ++i)
			for (int j = 1; j <= V; ++j)
				A[i][j] = 987654321;
		
		for (int i = 1, a, b, c; i <= E; ++i) {
			scanf("%d %d %d", &a, &b, &c);
			
			A[a][b] = min(A[a][b], c);
			A[b][a] = min(A[b][a], c);
		}		
		
		for (int i = 1, a, b, c; i <= W; ++i) {
			scanf("%d %d %d", &a, &b, &c);
			
			A[a][b] = min(A[a][b], -c);
		}		
		
		/* build graph */
		for (int i = 1; i <= V; ++i)
			for (int j = 1; j <= V; ++j) {
				if (A[i][j] != 987654321) {
					nodes[i].push_back(BOX(j, A[i][j]));
				}
			}

#ifdef DEBUG
		for (int i = 1; i <= V; ++i) {
			printf(" %d : ", i);
			for (int j = 0; j < nodes[i].size(); ++j) 
				printf("%d ", nodes[i][j]);
			printf("\n");
		}
#endif
		bool result = WARP();
		printf("%s\n", result ? "YES" : "NO");
			
	}
	
	return 0;
}
