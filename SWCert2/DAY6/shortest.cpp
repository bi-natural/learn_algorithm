#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>

#define DEBUG

using namespace std;


typedef long long INT64;

typedef pair<INT64, int> BOX;

typedef struct EDGE {
	int e;
	int w;
};

typedef struct NODE {
	int from;
	INT64 dist;
	vector<EDGE> edges;	
};

struct INPUT {
	int a, b, c;
};

const int MAX_N = 1000000;
const int MAX_E = 300000;
const INT64 MAX_C = 10000000000000ll;

int V, E;

NODE nodes[MAX_N+9];

INPUT A[MAX_N+9];

#if 0
class HEAP {

public:
	HEAP(int ma) { max_n = ma; n = 0;
		for (int i = 1; i <= max_n; ++i) {
			map[i] = i;
		}
	}
	bool isEmpty() { return n <= 0; }
	int PEEK() {
		BOX top = tree[1];
		
		swap(tree[1], tree[max_n])
		BUILD_HEAPDOWN(int n);
	}
	UPDATE(int idx, int value) {
		
	}
private:
	int n, max_n;
	int map[MAX_N+9];
	BOX tree[MAX_N+9];
	
	void BUILD_HEAPDOWN(int x){
		if (x >= n)
			return;
		
		NODE& a = tree[2*x];
		NODE& a = tree[2*x+1];
		
		if (x >) 
	}
		
};
#endif 

bool compare_A(const INPUT& x, const INPUT& y) { 
	if (x.a < y.a)
		return true;
	else if (x.a == x.a) {
		if (x.b == x.b)
			return x.c < x.c;
		return x.b < x.b;
	}
	return false;
}

struct compare_PQ {
	int operator()(const BOX& lhs, const BOX& rhs) { 
		return lhs.first > rhs.first;
	}
};

INT64 SHORTEST(int s, int e)
{
	priority_queue<BOX, vector<BOX>, compare_PQ> pq;

	nodes[s].dist = 0;
	pq.push(BOX(0, s));
	while (!pq.empty()) {
		BOX top = pq.top(); pq.pop();
#ifdef DEBUG
		printf(" -- pq.top & pop = (%lld, %d)\n", top.first, top.second);
#endif
		
		/* update adj. link */
		NODE& here = nodes[top.second];
		
		if (here.dist != top.first)
			continue;
			
		for (int i = 0; i < here.edges.size(); ++i) {
			EDGE& ei = here.edges[i];
			
			if ((here.dist + (INT64) ei.w) < nodes[ei.e].dist) {
				/* Relax */
#ifdef DEBUG
				printf("%d : new update %lld -> %lld\n", top.second, nodes[ei.e].dist, here.dist + (INT64)ei.w);
				printf(" -- pq.push = (%lld, %d) -- from %d\n", here.dist + (INT64)ei.w, ei.e, top.second);
#endif
				nodes[ei.e].dist = here.dist + (INT64)ei.w;
				nodes[ei.e].from = top.second;
				pq.push(BOX(here.dist + (INT64)ei.w, ei.e));
			}
			else {
#ifdef DEBUG
				printf("%d : skip (%d) dist = %lld < %lld\n", top.second, ei.e,  nodes[ei.e].dist, here.dist + (INT64)ei.w);
#endif				
			}
		}
	}
	
	return nodes[e].dist;
}

int main()
{
#ifdef DEBUG
	freopen("C:\\temp\\shortest.txt", "r", stdin);
	freopen("C:\\temp\\result.txt", "w", stdout);
#endif	
	scanf("%d %d", &V, &E);	
	
	for (int i = 1, a, b, c; i <= E; ++i) {
		scanf("%d %d %d", &A[i].a, &A[i].b, &A[i].c);
	}	
	
	for (int i = 1; i <= V; ++i)
		nodes[i].dist = MAX_C;
		
	sort(A+1, A+E+1, compare_A);
	int pa = A[1].a ;
	int pb = A[1].b ;
	
	EDGE e;
	int  from = A[1].a;
	int  to   = A[1].b;
	e.e = A[1].b, e.w = A[1].c;  nodes[A[1].a].edges.push_back(e);
	e.e = A[1].a, e.w = A[1].c;  nodes[A[1].b].edges.push_back(e);
	
	for (int i = 2; i <= E; ++i) {
		if (A[i].a == from && A[i].b == to) {
			continue;			
		}
		
		e.e = A[i].b, e.w = A[i].c;  
		nodes[A[i].a].edges.push_back(e);
		
		e.e = A[i].a, e.w = A[i].c;  
		nodes[A[i].b].edges.push_back(e);
		
		from = A[i].a;
		to = A[i].b;	
	}
		
#ifdef DEBUG
	for (int i = 1; i <= V; ++i) {
		printf("%d : ", i);
		for (int j = 0; j < nodes[i].edges.size(); ++j)
			printf("-> %d (%d) ", nodes[i].edges[j].e, nodes[i].edges[j].w);
		printf("\n");	
	}
#endif

	INT64 result = SHORTEST(1, V);
	if (result == MAX_C)
		printf("-1\n");
	else
		printf("%lld", result);
	return 0;
}
