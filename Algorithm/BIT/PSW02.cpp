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

class BIT {
	long long *ptree;
	int size;

public:
	BIT(int n) {
		size = n;
		ptree = new long long[n + 1];
		init();
	}
	~BIT() { delete[] ptree; }
	void init() {
		memset(ptree, 0, (size + 1)*sizeof(long long));
	}
	long long sum(int b) {
		long long sum = 0;
		for (; b; b -= LSB(b)) sum += ptree[b];
		return sum;
	}
	long long sum(int a, int b) {
		if (a == 1)
			return sum(b);
		else
			return sum(b) - sum(a - 1);
	}
	void add(int k, long long v) {
		for (; k <= size; k += LSB(k)) ptree[k] += v;
	}
	void dump_sum(char tag[], int s, int d) {
		printf("dump> %s :", tag);
		for (int i = s; i <= d; ++i)
			printf(" %lld", sum(i));
		printf("\n");
	}
};

const int MAX_N = 101;

int CASE, N, K;
int ins[MAX_N];
BIT bit(MAX_N + 1);

long long area(int s, int d)
{
	long long a = bit.sum(s, d);
	long long b = bit.sum(d + 1, N);

#ifdef DEBUG
	printf(" -- (%lld, %lld) = %d\n", b, a, a*b);
#endif
	return a * b;
}

bool optimize1(vector<long long>& v)
{
	int reduced = 0;
	long long gap = v[0];

#ifdef DEBUG
	printf("Current Answer = %lld, K = %d\n", gap, K);
	printf("Current = ");
	for (int k = 1; k <= K; ++k) {
		printf("[%d - %d] ", (int) v[k] + 1, (int) v[k + 1]);
	}
	printf("\n");
#endif

	for (int k = 1; k <= K; ++k) {
#ifdef DEBUG
		printf("> k = %d .. %d [next = %d]\n", (int) v[k] + 1, (int) v[k + 1], (int) v[k+2]-1);
#endif
		long long LastJ = v[k + 1];
		long long MaxDiff = 0;

		for (int i = (int) v[k] + 1, j = (int) v[k + 1] - 1; i < j; --j) {
			long long LB = bit.sum(i, j) * bit.sum(j + 1, (int) v[k + 1]);
			long long RT = bit.sum((int) v[k + 1] + 1, (int) v[k + 2]) * bit.sum(j + 1, (int) v[k + 2] - 1);

#ifdef DEBUG
			printf(" > LB = sum(%d, %d) * (%d, %d) = %lld\n", i, j, j + 1, (int) v[k + 1], LB);
			printf(" > RT = sum(%d, %d)]=%lld * sum(%d, %d)=%lld = %lld\n", (int) v[k + 1] + 1, (int) v[k + 2], bit.sum((int)v[k + 1] + 1, (int)v[k + 2]), j + 1, (int)v[k + 2] - 1, bit.sum(j + 1, (int)v[k + 2] - 1), RT);
#endif
			if ((LB >= RT) && (MaxDiff <= (LB - RT))) {
				reduced++;
				MaxDiff = max(MaxDiff, LB - RT);
#ifdef DEBUG
				printf("reduced!... again  CONT...  v[%d] = %d  (Diff = %lld, Current = %lld, Expected = %lld)\n", k + 1, j, LB - RT, gap, gap - MaxDiff);
#endif
				LastJ = (long long) j;
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
			printf("REDUCED.. v[%d] = %d  (NEW SUM = %lld)\n", k + 1, (int) LastJ, gap);
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
		initSum += ((long long) ins[i]) * ((long long) bit.sum(i));
	}

#ifdef DEBUG
	printf("debug> initial sum = %lld\n", initSum);
#endif

	ret.push_back(initSum);
	ret.push_back(0ll);

	for (int i = N - K, j = 1; i < N; ++i) {
		ret.push_back((long long) i);
		initSum -= area(j, i);
		j = i + 1;
	}

	ret.push_back((long long) N);
	ret[0] = initSum;

#ifdef DEBUG
	printf("debug> initial reduced = %lld\n", ret[0]);
#endif

	while (optimize1(ret))
		;

	return ret;
}

int main()
{
#ifdef DEBUG1
	freopen("C:\\temp\\sample_input.txt", "r", stdin);
	//freopen("C:\\temp\\input1.txt", "r", stdin);
	freopen("C:\\temp\\result.txt", "w", stdout);
#endif
	scanf("%d", &CASE);
	for (int t = 1; t <= CASE; ++t) {
		bool NK = false;

		scanf("%d %d", &N, &K);

		for (int i = 0; i < N; ++i) {
			scanf("%d", &ins[i]);
		}

		bit.init();
		for (int i = 1; i < N + 1; ++i) {
#ifdef DEBUG
			printf(" > add %d, %d\n", i, ins[i - 1]);
#endif
			bit.add(i, (long long) ins[i - 1]);
		}
#ifdef DEBUG
		bit.dump_sum("init", 1, N);
#endif

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
	}
}
