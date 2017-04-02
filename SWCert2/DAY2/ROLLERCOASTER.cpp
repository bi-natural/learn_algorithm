/*
 *
 * 롤러코스터
 *
 --
 소들은 롤러코스터를 짓고있다! 소들은 자신들이 가지고 있는 돈을 활용해서 최대한 재밌는 롤러코스터를 만들고 싶어한다.

롤러코스터는 직선형으로, 길이가 L이다. 소들이 롤러코스터를 지을 때, 롤러코스터는 
N개의 교체 가능한 부품들중 일부로 구성되어야 한다.

각 부품 i는 고정된 길이 Wi를 가지고 있다. 그리고 다양한 지형의 굴곡 때문에, i번째 부품은 오직 
Xi의 위치를 시작점으로만 놓을 수 있다.

소들은 다양한 롤러코스터를 0부터 L까지 빈틈없이 채우고 싶어한다. 만약 중간에 빈칸이 있으면 롤러코스터를 
구성할 수 없다. 또한, 각 부품끼리 겹쳐서 롤러코스터를 건설하는 경우도 없다.

각 i번째 부품은 "재미도" Fi과 짓는데 드는 비용 Ci가 있다. 총 비용은 롤러코스터를 구성하는 부품을의 
비용의 합으로 계산된다. 마찬가지로 총 재미도의 합은 롤러코스터를 구성하는 부품들의 재미도의 합으로 계산된다.

소들의 총 예산은 B이다. 소들을 도와 예산내에서 가장 큰 재미도를 가진 롤러코스터를 지을 수 있도록 도와주자!
 --
 
 풀이
 
 점화식
 
0 ~ x까지 이으면서, 재미도를 f만큼 얻고, 비용을 c만큼 쓸 수 있는가? D[x][f][c]  (true or false)
제한이 큰 변수를 빼내는 것이 이득! (f 제한: 100만, c 제한: 1000)
0 ~ x 까지 이으면서, 비용을 c만큼 썼을 때 얻을 수 있는 재미도D[x][c]


 D[x][c] = max(D[x ? W[i]][c ? C[i]] + F[i]) where X[i] + W[i] = x
           유의할 점: 모든 i에 대해서 실행하면 안되고, X[i] + W[i] = x인 i만 골라내야 한다.
           
 
 */ 

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <map>
#include <algorithm>

using namespace std;

#define DEBUG 

const int MAX_N = 10000;
const int MAX_L = 1000;
const int MAX_B = 1000;

typedef long long INT64;
struct part {
	int x, w, f, c;
};

bool compare_x(const part& a, const part& b)
{
	return a.x < b.x;
}

int L, N, B;
part A[MAX_N + 9];

int dp[MAX_L + 9][MAX_B+9];
multimap<int, int> starts;

int lowerbound(part B[], int BN, int x)
{
	int low = 1, high = BN+1;

	while (low <= high) {
		int mid = (low + high) / 2;
		if (x < B[mid].x)
			high = mid - 1;
		else if (x > B[mid].x)
			low = mid + 1;
		else
			return mid;
	}
	return low;
}

int ROLLERCOAST(int start, int budget)
{
	static int isfirst = true;

#ifdef DEBUG
	printf("Enter (%d, %d)\n", start, budget);
#endif
	int& ref = dp[start][budget];

	if (ref != -1)
		return ref;

	if (start > L || budget < 0)
		return ref =  -10000000;

	if (start == L)
		return ref = 0;

	if (isfirst)
	{
		isfirst = false;
		sort(A + 1, A + N + 1, compare_x);
	}
	
	int idx = lowerbound(A, N, start);

#ifdef DEBUG
	printf("lb(%d) --> %d (%d)\n", start, idx, A[idx]);
#endif

	if (idx == (N + 1))
		return ref = 0;

	ref = 0;
	for (int i = idx; i <= N; ++i)
	{
		if (A[i].x != start)
			break;

		/* Use This Part */
		int used = A[i].f + ROLLERCOAST(start + A[i].w, budget - A[i].c);

		if (used > 0)
			ref = max(ref, used);
	}

	return ref;
}

int ROLLERCOAST_map(int start, int budget)
{
	static int isfirst = true;

#ifdef DEBUG
	printf("Enter (%d, %d)\n", start, budget);
#endif
	int& ref = dp[start][budget];

	if (ref != -1)
		return ref;

	if (start == L)
		return ref = 0;

	ref = -100000000;

	pair<multimap<int, int>::iterator, multimap<int, int>::iterator> iterPair = starts.equal_range(start);

	for (multimap<int, int>::iterator iter = iterPair.first; iter != iterPair.second; ++iter)
	{
		int& selected = iter->second;

#ifdef DEBUG
		printf("![%d][%d] -- map.equal_range(%d) --> %d\n", start, budget, start, selected);
#endif
		/* Possible: Use This Part */
		if (A[selected].c <= budget && (start + A[selected].w <= L))
		{
			int subproblem = ROLLERCOAST_map(start + A[selected].w, budget - A[selected].c);

			if (subproblem >= 0 && (A[selected].f + subproblem > ref))
			{
				ref = A[selected].f + subproblem;
#ifdef DEBUG
				printf("![%d][%d] -- new updated = %d\n", start, budget, ref);
#endif 
			}
		}
	}

#ifdef DEBUG
	if (ref < 0)
	{
		printf("![%d][%d] --- not found...\n", start, budget);
	}
#endif
	return ref;
}

int main()
{
#ifdef DEBUG
	freopen("C:\\temp\\rollercoast.txt", "r", stdin);
	freopen("C:\\temp\\result.txt", "w", stdout);
#endif

	starts.clear();
	scanf("%d %d %d", &L, &N, &B);
	for (int i = 1; i <= N; ++i) {
		part& p = A[i];
		scanf("%d %d %d %d", &p.x, &p.w, &p.f, &p.c);
		starts.insert(pair<int, int>(p.x, i));
	}
	
	memset(dp, -1, sizeof(dp));

	int result = ROLLERCOAST_map(0, B);
	int max_result = -1;

#ifdef DEBUG
	for (int i = 1; i <= B; ++i)
		printf("%5d", dp[0][i]);
	printf("\n");
#endif
	for (int i = 1; i <= B; ++i)
		max_result = max(max_result, dp[0][i]);

	if (max_result != 0)
		printf("%d\n", max_result);
	else
		printf("-1\n");
}
