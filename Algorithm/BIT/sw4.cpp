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
const int MAX_M = 11;

class BIT {
	INT64 tree[MAX_N + 1];
	int size;

public:
	void init(int n) {
		size = n;
		memset(tree, 0, sizeof(tree));
	}

	INT64 sum(int b) {
		INT64 sum = 0;
		for (; b; b -= LSB(b)) sum += tree[b];
		return sum;
	}

	INT64 sum(int a, int b) {
		if (a == 1)
			return sum(b);
		else
			return sum(b) - sum(a - 1);
	}

	void add(int k, INT64 v) {
		for (; k <= size; k += LSB(k)) tree[k] += v;
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

INT64 cache[MAX_M+1][MAX_N+1];
INT64 initMax;
int   choices[MAX_M+1][MAX_N+1];

INT64 findMinSet(int level, int d, int leftM)
{
	char level_buf[200];

	memset(level_buf, '\0', sizeof(level_buf));
	for (int i = 0; i < (level*2); i += 2) {
		level_buf[i] = ' ';
		level_buf[i+1] = ' ';
	}

	if (d > N || leftM < 0)
		return 0ll;

	INT64& ref = cache[leftM][d];

	if (leftM == (N-d+1)) {
		choices[N-d+1][d] = d;

#ifdef DEBUG
		printf("%s findMin(%d,%d) M=N (%d = %d)\n", level_buf, d, leftM, leftM, N - d + 1);
		printf("%s findMin(%d,%d) choices[i=%d] = %d\n", level_buf, d, leftM, N - d + 1, d);
#endif

		return ref = findMinSet(level+1, d+1, leftM-1);
	}

	if (ref != -1ll) {
#ifdef DEBUG
		printf("%s findMin(%d,%d) [day=%d] --> cache : %lld\n", level_buf, d, leftM, choices[leftM][d], ref);
#endif
		return ref;
	}

	ref = initMax;

	/* leftM is '1', and today(d) is not end of days */
	if (leftM == 1)
	{
		/* [*TODO*] binary search*/
		for (int i = d; i <= N; ++i) {
			if (CSUM[d-1][i] > ref) {
#ifdef DEBUG
				printf("%s findMin(%d,%d) M=1 CSUM(i=%d,N=%d,v=%lld) > ref=%lld CONT...\n", level_buf, d, leftM, d-1, i, CSUM[d-1][i], ref);
				continue;
#endif
			}

			INT64 v = CSUM[d-1][i] + CSUM[i][N];

#ifdef DEBUG
			printf("%s findMin(%d,%d) M=1 : CSUM(i=%d,N=%d,v=%lld) + CSUM(j=%d,N=%d,v=%lld) --> %lld\n", level_buf, d, leftM, d, i, CSUM[d-1][i], i, N, CSUM[i][N], v);
#endif
			if (v < ref) {
#ifdef DEBUG
				printf("%s +--> findMin(%d,%d) MIN change [day=%d] %lld -> %lld, day[%d] = %d\n", level_buf, d, leftM, i, ref, v, leftM, i);
#endif
				ref = v;
				choices[leftM][d] = i;
			}
		}

		return ref;
	}

	for (int i = d; i <= (N - leftM+1); ++i) {
		/* select between [i+1 .. (N-leftM+1)] */
#ifdef DEBUG
		printf("%s findMin(%d,%d) : CSUM(i=%d,j=%d,v=%lld) + findMinSet(%d, %d) --> CALL...\n", level_buf, d, leftM, d-1, i, CSUM[d-1][i], i+1, leftM-1);
#endif
		if (CSUM[d - 1][i] > ref)
		{
#ifdef DEBUG
			printf("%s findMin(%d,%d) : CSUM(i=%d,N=%d,v=%lld) > ref=%lld CONT...\n", level_buf, d, leftM, d-1, i, CSUM[d-1][i], ref);
			continue;
#endif
		}

		INT64 v, f;

		/* choice [i] */
		v = CSUM[d - 1][i] + findMinSet(level+1, i+1, leftM-1);
#ifdef DEBUG
		printf("%s findMin(%d,%d) : CSUM(%d)= %lld + findMinSet(i+1=%d, leftM-1=%d) --> RET =  %lld\n", level_buf, d, leftM, i, CSUM[d-1][i], i+1, leftM-1, v);
#endif
		if (v < ref) {
#ifdef DEBUG
			printf("%s +--> findMin(%d,%d) MIN change [day=%d] %lld -> %lld, day[%d] = %d\n", level_buf, d, leftM, i, ref, v, leftM, i);
#endif
			ref = v;
			choices[leftM][d] = i;
		}
	}

	return ref;
}

INT64 solve()
{
	memset(cache, -1ll, sizeof(cache));
	memset(choices, -1, sizeof(choices));

	initMax = BSUM[N];

	return findMinSet(0, 1, M);
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
		scanf("%d %d", &N, &M);

		for (int i = 1; i <= N; ++i) {
			scanf("%lld", &A[i]);
		}

		ABIT.init(MAX_N);
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
		for (int i = M, d = 1; i >= 1; --i, ++d) {
			d = choices[i][d];
			printf(" %d", d);
		}
		printf("\n");
	}
}
