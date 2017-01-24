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

#if 0
bool optimize1(vector<long long>& v)
{
	int reduced = 0;
	long long gap = v[0];

#ifdef DEBUG
	printf("Current Answer = %lld, K = %d\n", gap, K);
	printf("Current = ");
	for (int k = 1; k <= K; ++k) {
		printf("[%d - %d] ", (int)v[k] + 1, (int)v[k + 1]);
	}
	printf("\n");
#endif

	for (int k = 1; k <= K; ++k) {
#ifdef DEBUG
		printf("> k = %d .. %d [next = %d]\n", (int)v[k] + 1, (int)v[k + 1], (int)v[k + 2] - 1);
#endif
		long long LastJ = v[k + 1];
		long long MaxDiff = 0;

		for (int i = (int)v[k] + 1, j = (int)v[k + 1] - 1; i < j; --j) {
			long long LB = bit.sum(i, j) * bit.sum(j + 1, (int)v[k + 1]);
			long long RT = bit.sum((int)v[k + 1] + 1, (int)v[k + 2]) * bit.sum(j + 1, (int)v[k + 2] - 1);

#ifdef DEBUG
			printf(" > LB = sum(%d, %d) * (%d, %d) = %lld\n", i, j, j + 1, (int)v[k + 1], LB);
			printf(" > RT = sum(%d, %d)]=%lld * sum(%d, %d)=%lld = %lld\n", (int)v[k + 1] + 1, (int)v[k + 2], bit.sum((int)v[k + 1] + 1, (int)v[k + 2]), j + 1, (int)v[k + 2] - 1, bit.sum(j + 1, (int)v[k + 2] - 1), RT);
#endif
			if ((LB >= RT) && (MaxDiff <= (LB - RT))) {
				reduced++;
				MaxDiff = max(MaxDiff, LB - RT);
#ifdef DEBUG
				printf("reduced!... again  CONT...  v[%d] = %d  (Diff = %lld, Current = %lld, Expected = %lld)\n", k + 1, j, LB - RT, gap, gap - MaxDiff);
#endif
				LastJ = (long long)j;
			}
			else
			{
				break;
			}
		}

		gap -= MaxDiff;
		v[k + 1] = LastJ;
#ifdef DEBUG
		if (reduced > 0)
			printf("REDUCED.. v[%d] = %d  (NEW SUM = %lld)\n", k + 1, (int)LastJ, gap);
#endif
	}

	v[0] = gap;

	return (reduced > 0);
}

vector<long long> healthboy2()
{
	vector<long long> ret;

	long long initSum = 0;
	for (int i = 1; i <= N; ++i) {
		initSum += ((long long)ins[i]) * ((long long)bit.sum(i));
	}

#ifdef DEBUG
	printf("debug> initial sum = %lld\n", initSum);
#endif

	ret.push_back(initSum);
	ret.push_back(0ll);

	for (int i = N - K, j = 1; i < N; ++i) {
		ret.push_back((long long)i);
		initSum -= area(j, i);
		j = i + 1;
	}

	ret.push_back((long long)N);
	ret[0] = initSum;

#ifdef DEBUG
	printf("debug> initial reduced = %lld\n", ret[0]);
#endif

	while (optimize1(ret))
		;

	return ret;
}
#endif

INT64 cache[11][MAX_N+1];
INT64 currentMin;

INT64 findMinSet(vector<int>& s, int d, int leftM)
{
	INT64& ref = cache[leftM][d];

	if (leftM == N) {
		currentMin = 0ll;
		for (int i = 1; i <= N; ++i) {
			s.push_back(i);
		}
		return currentMin;
	}

	if (ref != -1ll) { return 0ll; }

	if (leftM == 1)
	{	
		ref = currentMin;

		int selected = d;

		/* [TODO] binary search*/
		for (int i = d; i < N; ++i) {
			for (int j = d+1; (CSUM[d][i] < currentMin) && (j < N); ++j) {
				INT64 v = CSUM[d][i] + CSUM[i][N];

				if (v < ref) {
					ref = v;
					selected = i;
				}
			}
		}

		s.push_back(selected);
		return ref;
	}

	ref = currentMin;

	int selected = d;

	for (int base = d; base <= N - leftM; ++base) {
		for (int j = base + 1; (CSUM[base][j] < currentMin) && (j < N); ++j) {
			INT64 v = CSUM[base][j] + findMinSet(s, j, leftM -1);

			if (v < ref) {
				ref = v;
				selected = j;
			}
		}
	}

	s.push_back(selected);
	return ref;

}

INT64 solve(vector<int>& s)
{
	memset(cache, -1ll, sizeof(cache));
	currentMin = BSUM[N];

	return findMinSet(s, 1, M);
}

int main()
{
#ifdef DEBUG1
	//freopen("sample_input.txt", "r", stdin);
	freopen("sw12.txt", "r", stdin);
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
					printf("debug> CSUM[%d][%d],v=%lld === BSUM[j=%d,v=%lld] - BSUM[i=%d,v=%lld] - ABIT.RANGE(%d,%d,v=%lld)*ABIT.RANGE(%d,v=%lld) --> %lld\n",
						i, j, CSUM[i][j], j, BSUM[j], i, BSUM[i], i + 1, j, ABIT.sum(i + 1, j), i, ABIT.sum(i), ABIT.sum(i + 1, j) * ABIT.sum(i));
				}
				else {
					CSUM[i][j] = BSUM[j];
				}	
			}
		}

		for (int i = 0; i <= N; ++i) {
			for (int j = 1; j <= N; ++j) {
				printf(" %05lld", CSUM[i][j]);
			}
			printf("\n");
		}

		vector<int> selected;

		selected.clear();
		INT64 result = solve(selected);

		printf("#%d %lld\n", t, result);
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
