/* Health Boy */
#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

#define LSB(s)	((s)&(-s))

class BIT {
	int *ptree, size;

public:
	BIT(int n) {
		size = n;
		ptree = new int[n + 1];
		init();
	}
	~BIT() { delete[] ptree; }
	void init() {
		memset(ptree, 0, (size + 1)*sizeof(int));
	}
	int sum(int b) {
		int sum = 0;
		for (; b; b -= LSB(b)) sum += ptree[b];
		return sum;
	}
	int sum(int a, int b) {
		if (a == 1)
			return sum(b);
		else
			return sum(b) - sum(a - 1);
	}
	void add(int k, int v) {
		for (; k <= size; k += LSB(k)) ptree[k] += v;
	}
	void dump_sum(char tag[], int s, int d) {
		printf("dump> %s :", tag);
		for (int i = s; i <= d; ++i)
			printf(" %d", sum(i));
		printf("\n");
	}
};

const int MAX_N = 100;

int CASE, N, K;
int ins[MAX_N];
BIT bit(MAX_N + 1);

int area(int s, int d)
{
	int a = bit.sum(s, d);
	int b = bit.sum(d + 1, N);

	printf(" -- (%d, %d) = %d\n", b, a, a*b);
	return a * b;
	//return bit.sum(s, d) * bit.sum(s + 1, N-1);
}

vector<int> healthboy()
{
	vector<int> ret;

	int orgSum = 0;
	for (int i = 1; i <= N; ++i) {
		orgSum += ins[i] * bit.sum(i);
	}
	printf("debug> original sum = %d\n", orgSum);

	ret.push_back(orgSum);

	int delta = orgSum;

	ret.push_back(0);
	for (int i = N-K, j = 1; i < N; ++i) {
		ret.push_back(i);
		delta -= area(j, i);
		j = i+1;
	}
	ret.push_back(N);

	printf("Current Delta = %d\n", delta);

	int reduced = 0;

	for (int k = 1; k <= K; ++k) {
		printf(" k = %d\n", k);

		bool changed = false;
		int LastJ;
		int LastLB, LB;
		int MaxDiff = 0;
		int LastRT, RT = 0;

		for (int i = ret[k], j = ret[k + 1] - 1; i <= j; --j) {
			LB  = bit.sum(i + 1, j) * bit.sum(j+1, ret[k+1]);
			RT  = ins[ret[k+1]] * bit.sum(j + 1, ret[k + 2] - 1);

			printf(" > LB = (%d, %d) * (%d, %d) = %d\n", i + 1, j, j + 1, ret[k + 1], LB);
			printf(" > RT = ins[%d]=%d * sum(%d, %d)=%d = %d\n", ret[k+1], ins[ret[k+1]], j + 1, ret[k + 2]-1, bit.sum(j + 1, ret[k + 2]-1), RT);

			if ((LB >= RT) && (MaxDiff <= (LB-RT))) {
				MaxDiff = max(MaxDiff, LB - RT);
				printf("reduced!... again  CONT...  ret[%d] = %d  (Diff = %d, S = %d)\n", k+1, j, LB - RT, delta - MaxDiff);
				LastJ = j;
				LastLB = LB;
				LastRT = RT;
			}
			else
			{
				delta -= MaxDiff;
				ret[k+1] = LastJ;
				changed = true;
				printf("increased.  BREAK.  ret[%d] = %d  (NEW SUM = %d)\n", k+1, LastJ, delta);
				break;
			}
		}
	}

	ret[0] = delta;
	return ret;
}

vector<int> healthboy2()
{
	vector<int> ret;
	vector<int> vec;

	int orgSum = 0;
	for (int i = 1; i <= N; ++i) {
		orgSum += ins[i] * bit.sum(i);
	}
	printf("debug> original sum = %d\n", orgSum);

	ret.push_back(orgSum);

	int delta = orgSum;

	vec.push_back(0);
	for (int i = N-K, j = 1; i < N; ++i) {
		vec.push_back(i);
		delta -= area(j, i);
		j = i+1;
	}
	vec.push_back(N);

	printf("Current Delta = %d\n", delta);

	int reduced = 0;

	for (int k = 0; k < K; ++k) {
		printf(" k = %d\n", k);

		bool changed = false;
		int LastJ;
		int LastLB, LB;
		int MaxDiff = 0;
		int LastRT, RT = 0;

		for (int i = vec[k], j = vec[k + 1] - 1; i <= j; --j) {
			LB  = bit.sum(i + 1, j) * bit.sum(j+1, vec[k+1]);
			RT  = ins[vec[k+1]] * bit.sum(j + 1, vec[k + 2] - 1);

			printf(" > LB = (%d, %d) * (%d, %d) = %d\n", i + 1, j, j + 1, vec[k + 1], LB);
			printf(" > RT = ins[%d]=%d * sum(%d, %d)=%d = %d\n", vec[k+1], ins[vec[k+1]], j + 1, vec[k + 2]-1, bit.sum(j + 1, vec[k + 2]-1), RT);

			if ((LB >= RT) && (MaxDiff <= (LB-RT))) {
				MaxDiff = max(MaxDiff, LB - RT);
				printf("reduced!... again  CONT...  vec[%d] = %d  (Diff = %d, S = %d)\n", k+1, j, LB - RT, delta - MaxDiff);
				LastJ = j;
				LastLB = LB;
				LastRT = RT;
			}
			else
			{
				delta -= MaxDiff;
				vec[k+1] = LastJ;
				changed = true;
				printf("increased.  BREAK.  vec[%d] = %d  (NEW SUM = %d)\n", k+1, LastJ, delta);
				break;
			}
		}
	}

	ret.push_back(delta);
	for (int i = 0; i < vec.size(); ++i)
		ret.push_back(vec[i]);

	return ret;
}

int main()
{
	freopen("sw12.txt", "r", stdin);
	freopen("result.txt", "w", stdout);
	scanf("%d", &CASE);
	for (int t = 1; t <= CASE; ++t) {
		scanf("%d %d", &N, &K);
		for (int i = 0; i < N; ++i) {
			scanf("%d", &ins[i]);
		}
		bit.init();
		for (int i = 1; i < N + 1; ++i) {
			printf(" > add %d, %d\n", i, ins[i - 1]);
			bit.add(i, ins[i - 1]);
		}
		bit.dump_sum("init", 1, N);

		vector<int> result = healthboy();
		printf("#%d %d", t, result[0]);
		for (int i = 2; i < result.size() - 1; ++i) {
			printf(" %d", result[i]);
		}
		printf("\n");
	}
}
