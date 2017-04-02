/*
 * ¾Æ·Î¸¶
 *
 --
 --
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

#define DEBUG
#define DEBUG1

typedef long long INT64;
const int MAX_N = 1007;
const int MAX_E = 100007;
const int MAX_H = 1007;

int CASE;
int N;

int EXPECTED_LITMIT_TIME;

struct oil {
	int expire;
	int time;
	int minlife() {
		return time;
	}
	int maxlife() {
		return expire + time;
	}
};

int best_time;

oil oils[MAX_N];

typedef unsigned long long UINT64;
const int UINT64_SIZE = sizeof(UINT64);

struct used {
	UINT64 bits[(MAX_N / UINT64_SIZE) + 1];
	void init() { memset(bits, 0, sizeof(bits)); }
	bool check(int t) { return (bits[t / UINT64_SIZE] & (1ull << (t % UINT64_SIZE))); }
	void set(int t) { bits[t / UINT64_SIZE] |= (1ull << (t % UINT64_SIZE)); }
	void unset(int t) { bits[t / UINT64_SIZE] ^= (1ull << (t % UINT64_SIZE)); }
};

struct fastIndex {
	int value, idx;

	fastIndex() : value(0), idx(0) {};
	fastIndex(const int& v, const int& i) {
		value = v, idx = i;
	}
};

bool compare_by_expire_plus_last_asc(const fastIndex&a, const fastIndex& b) { return (a.value < b.value); }

fastIndex aroma_lastIndex[MAX_N + 9];		/* ? í†µê¸°í•œ */
fastIndex arama_sumIndex[MAX_N + 9];		/* ? í†µê¸°í•œ + ì§€?ì‹œê°?*/
fastIndex aroma_expireIndex[MAX_N + 9];

int D[MAX_E + MAX_H + 9];
int fwd_advanced[MAX_H + MAX_E + 9];
int newfwd_advanced[MAX_H + MAX_E + 9];

int AROMA_fwd2()
{
	int a_MAX, n_MAX;
	int max_advanced = 0;

	memset(D, 0, sizeof(D));
	memset(fwd_advanced, 0, sizeof(fwd_advanced));
	memset(newfwd_advanced, 0, sizeof(newfwd_advanced));

	D[0] = 1;
	fwd_advanced[0] = 0;
	a_MAX = 1;

	for (int i = 1; i <= N; ++i) {
		int& idx = arama_sumIndex[i].idx;
		oil& found = oils[idx];

		n_MAX = 0;
		for (int j = 0; j < a_MAX; ++j)
		{
			if (found.expire >= fwd_advanced[j])
			{
				int advanced = found.time + fwd_advanced[j];

				if (!D[advanced]) {
					if (max_advanced < advanced)
						max_advanced = advanced;

					if (max_advanced >= EXPECTED_LITMIT_TIME)
					{
						return max_advanced;
					}

					newfwd_advanced[n_MAX++] = advanced;
					D[advanced] = 1;
				}
			}
		}

		for (int ni = 0; ni < n_MAX; ++ni)
			fwd_advanced[a_MAX++] = newfwd_advanced[ni];
	}

	return max_advanced;
}

int do_test[100] = { 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1  /* 11 */, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, };

int main()
{
#ifdef DEBUG1
	// freopen("C:\\temp\\ideone_long.txt", "r", stdin);
	freopen("C:\\temp\\ideone_long.txt", "r", stdin);
	freopen("C:\\temp\\result.txt", "w", stdout);
#endif

	scanf("%d", &CASE);
	for (int t = 1; t <= CASE; ++t)
	{
		int sum_of_lasttime = 0;
		int max_of_exp_last = 0;

		memset(oils, 0, sizeof(oils));
		memset(arama_sumIndex, 0, sizeof(arama_sumIndex));

		scanf("%d", &N);
		for (int i = 1; i <= N; ++i)
		{
			oil& oil = oils[i];

			scanf("%d %d", &oil.expire, &oil.time);
			sum_of_lasttime += oil.time;
		}

		sort(arama_sumIndex + 1, arama_sumIndex + N + 1, compare_by_expire_plus_last_asc);
		max_of_exp_last = oils[arama_sumIndex[N].idx].maxlife();
		EXPECTED_LITMIT_TIME = min(sum_of_lasttime, max_of_exp_last);

		int result = AROMA_fwd2();
		printf("#%d %d\n", t, result);
	}
	return 0;
} 
