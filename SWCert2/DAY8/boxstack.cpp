/* 책장 쌓기 */
#include <cstdio> 
#include <cstdlib>
#include <queue>
#include <algorithm>

#define DEBUG
#define MAX_M	100007
#define MAX_W	  1007

using namespace std;

typedef long long INT64;

struct BOX {
	int m;
	int w;
	BOX() {}
	BOX(const int& x, const int& y) : m(x), w(y) {} 
};

const int MAX_N = 100000;
int CASE;
int N;

BOX A[MAX_N+9];

bool compare_SORT(const BOX& lhs, const BOX& rhs) 
{
	return lhs.m + lhs.w > rhs.m + rhs.w;	
}

int BOX_STACK()
{
	vector<BOX> boxstack;
	BOX* search = A + 1;
	
	while (search != (A + N + 1)) {
#ifdef DEBUG
		printf(" -- searched %d (m=%d, w=%d)\n", distance(search, A+1), search->m, search->w);
#endif
		boxstack.push_back(*search);		
		BOX* search = lower_bound(A + 1, A + N + 1, BOX(search->m, 0), compare_SORT);
	}
	
	int result = 0;
	for (int i = 0; i < boxstack.size(); ++i) 
		result += boxstack[i].w;
		
	return result;
}

bool compare_SORT_asc(const BOX& lhs, const BOX& rhs) 
{
	return lhs.m + lhs.w < rhs.m + rhs.w;	
}

/* 
 * 
 * D[i] : i번째 Box까지 사용해서 쌓을 수 있는 것중에서 무게가 가장 큰 것 
 */
 
int D[MAX_M + MAX_W + 7];

int BOX_STACK2()
{
	/* 용량(견딜수있는 무게) + 자기자신의 무게 순서로 오름차순으로 정렬 */ 
	sort(A + 1, A + N + 1, compare_SORT_asc);
	
	D[1] = A[1].w;
	for (int i = 2; i <= N; ++i) {
		for (int j = 1; j < i; ++j) {
			if (D[j] <= A[j].m) {
				D[i] = D[j] + A[i].w;
			}
		}
	}
	
	int maxWeight = 0;
	
	for (int i = 1; i <= N; ++i)
		maxWeight = max(maxWeight, D[i]);
		
	return maxWeight;
}

int main()
{
#ifdef DEBUG
	freopen("C:\\temp\\boxstack.txt", "r", stdin);
	//freopen("C:\\temp\\result.txt", "w", stdout);
#endif	
	scanf("%d", &CASE);	
	
	for (int t = 1; t <= CASE; ++t) {
		scanf("%d", &N);
		
		for (int i = 1, a, b; i <= N; ++i) {
			BOX& p = A[i];
			scanf("%d %d", &p.m, &p.w);
		}
		
		sort(A+1, A+N+1, compare_SORT);
		
#ifdef DEBUG11
		for (int i = 1; i <= N; ++i) {
			printf("(%d, %d, %d) ", A[i].m, A[i].w, A[i].m + A[i].w);
		}
		printf("\n");
#endif

		int result = BOX_STACK2();
		printf("#%d %d\n", t, result);
	}
	return 0;
}
