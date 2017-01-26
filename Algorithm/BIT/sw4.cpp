/* Health Boy */
#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

#define LSB(s)	((s)&(-s))

#define DEBUG
#define DEBUG1

typedef long long INT64;
const int MAX_N = 101;

class BIT {
	INT64 ptree[MAX_N + 1];
	int size;

public:
	void init(int n) {
		size = n;
		memset(ptree, 0, sizeof(ptree));
	}

	INT64 sum(int b) {
		INT64 sum = 0;
		for (; b; b -= LSB(b)) sum += ptree[b];
		return sum;
	}

	INT64 sum(int a, int b) {
		if (a == 1)
			return sum(b);
		else
			return sum(b) - sum(a - 1);
	}

	void add(int k, INT64 v) {
		for (; k <= size; k += LSB(k)) ptree[k] += v;
	}

	void dump_sum(char tag[], int s, int d) {
		printf("dump> %s :", tag);
		for (int i = s; i <= d; ++i)
			printf(" %lld", sum(i));
		printf("\n");
	}
};


INT64 A[MAX_N + 1];
BIT   ABIT;
INT64 BSUM[MAX_N + 1];
INT64 CSUM[MAX_N + 1][MAX_N + 1];

int CASE, N, M;

INT64 cache[11][MAX_N+1];
INT64 initMax;
int   cacheDay[11];

INT64 findMinSet(int d, int leftM)
{
	INT64& ref = cache[leftM][d];

	if (leftM == (N-d+1)) {
		for (int i = leftM, k = d; i >= d; --i, --k) {
			cacheDay[i] = N-i+1;
			// cache[i][k] = findMinSet(k +1, i -1);
		}
		return ref = 0ll;
	}

	if (ref != -1ll) { 
#ifdef DEBUG
		printf("\t- findMin(%d,%d) [day=%d] --> cache : %lld\n", d, leftM, cacheDay[leftM], ref);
#endif
		return ref; 
	}

	ref = initMax;

	if (leftM == 1)
	{		
		/* [*TODO*] binary search*/
		for (int i = d; i <= N; ++i) {
			if (CSUM[d-1][i] > ref)
				break;

			INT64 v = CSUM[d-1][i] + CSUM[i][N];

#ifdef DEBUG
			printf("\t- findMin(%d,%d) leftM=1 : CSUM(i=%d,N=%d,v=%lld) + CSUM(j=%d,N=%d,v=%lld) --> %lld\n", d, leftM, d, i, CSUM[d][i], i, N, CSUM[i][N], v);
#endif
			if (v <= ref) {
#ifdef DEBUG
				printf("\t- findMin(%d,%d) MIN change [day=%d] %lld -> %lld, day[%d] = %d\n", d, leftM, i, ref, v, leftM, i);
#endif
				ref = v;
				cacheDay[leftM] = i;
			}
		}

		return ref;
	}

	for (int i = d; i <= (N - leftM+1); ++i) {
		/* select between [i+1 .. (N-leftM+1)] */
#ifdef DEBUG
		printf("+ findMin(%d,%d) leftM=%d : CSUM(i=%d,j=%d,v=%lld) + findMinSet(...) --> CALL...\n", d, leftM, leftM, d-1, i, CSUM[d-1][i]);
#endif
		if (CSUM[d - 1][i] > ref)
		{
			break;
		}

		INT64 v = CSUM[d-1][i] + findMinSet(i+1, leftM-1);
#ifdef DEBUG
		printf("+ findMin(%d,%d) leftM=%d : + findMinSet(%j=%d, leftM=%d) == %lld\n", d, leftM, leftM, i+1, leftM-1, v);
#endif
		if (v <= ref) {
#ifdef DEBUG
			printf("+ findMin(%d,%d) MIN change [day=%d] %lld -> %lld, day[%d] = %d\n", d, leftM, i, ref, v, leftM, i);
#endif
			ref = v;
			cacheDay[leftM] = i;
		}
	}

	return ref;
}

INT64 solve()
{
	memset(cache, -1ll, sizeof(cache));
	memset(cacheDay, -1, sizeof(cacheDay));

	initMax = BSUM[N];

	return findMinSet(1, M);
}

int main()
{
#ifdef DEBUG1
	freopen("sample_input.txt", "r", stdin);
	//freopen("sw12.txt", "r", stdin);
	freopen("result.txt", "w", stdout);
#endif

	scanf("%d", &CASE);
	for (int t = 1; t <= CASE; ++t) {
		bool MK = false;

		scanf("%d %d", &N, &M);

		for (int i = 1; i <= N; ++i) {
			scanf("%lld", &A[i]);
		}

		ABIT.init(N);
		for (int i = 1; i <= N; ++i) {
#ifdef DEBUG
			printf(" > add %d, %lld\n", i, A[i]);
#endif
			ABIT.add(i, A[i]);
		}
#ifdef DEBUG
		ABIT.dump_sum("ABIT(init)", 1, N);
#endif

		memset(BSUM, 0, sizeof(BSUM));
		for (int i = 2; i <= N; ++i)
			BSUM[i] = BSUM[i - 1] + A[i] * ABIT.sum(i - 1);

#ifdef DEBUG
		printf("BSUM(init):");
		for (int i = 1; i <= N; ++i)
			printf(" %lld", BSUM[i]);
		printf("\n");
#endif

		for (int i = 0; i < N; ++i) {
			for (int j = i+1; j <= N; ++j) {
				if (i) {
					CSUM[i][j] = BSUM[j] - BSUM[i] - ABIT.sum(i + 1, j) * ABIT.sum(i);
#ifdef DEBUG
					printf("debug> CSUM[%d][%d],v=%lld === BSUM[j=%d,v=%lld] - BSUM[i=%d,v=%lld] - ABIT.RANGE(%d,%d,v=%lld)*ABIT.RANGE(%d,v=%lld) --> %lld\n",
						i, j, CSUM[i][j], j, BSUM[j], i, BSUM[i], i + 1, j, ABIT.sum(i + 1, j), i, ABIT.sum(i), ABIT.sum(i + 1, j) * ABIT.sum(i));
#endif
				}
				else {
					CSUM[i][j] = BSUM[j];
				}	
			}
		}

#ifdef DEBUG
		for (int i = 0; i <= N; ++i) {
			for (int j = 1; j <= N; ++j) {
				printf(" %05lld", CSUM[i][j]);
			}
			printf("\n");
		}
#endif
		INT64 result = solve();

		printf("#%d %lld", t, result);
		for (int i = M; i >= 1; --i) {
			printf(" %d", cacheDay[i]);
		}
		printf("\n");

		// printf("\n = %lld + %lld + %lld = %lld\n", BSUM[3], CSUM[3][6], CSUM[6][N], BSUM[3] + CSUM[3][6] + CSUM[6][N]);
#if 0
		NK = (N == K);
		if (NK)
			--K;

		vector<long long> result = healthboy2();

		printf("#%d %lld", t, result[0]);
		for (int i = 2; i < result.size() - 1; ++i) {
			printf(" %lld", result[i]);
		}
		if (NK)
			printf(" %d", N);

		printf("\n");
#endif
	}
}
