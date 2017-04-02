/* DP: 프리랜서의 일정 */

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <map>
#include <algorithm>

using namespace std;

#define DEBUG

typedef long long INT64;

const int MAX_WORKS = 100000;
const int MAX_VALUE = 1000000000;

int CASE;
int N;

struct schedule {
	int s, e, c;
};

schedule A[MAX_WORKS + 9];

multimap<INT64, int> end_days;

INT64 dp[MAX_WORKS + 9];

INT64 FREELANCER(INT64 ew)
{
	INT64& ref = dp[ew];

	if (ref != -1)
		return ref;


	return ref;
}

int main()
{
#ifdef DEBUG
	freopen("C:\\temp\\freelancer.txt", "r", stdin);
	freopen("C:\\temp\\result.txt", "w", stdout);
#endif
	scanf("%d", &CASE);

	for (int t = 1; t <= CASE; ++t)
	{
		INT64 maxE = -1;

		scanf("%d", &N);

		end_days.clear();
		for (int i = 1; i <= N; ++i) {
			schedule& s = A[i];

			scanf("%d %d %d", &s.s, &s.e, &s.c);

			end_days.insert(pair<INT64, int>(s.e, i));

			maxE = max(maxE, (INT64)(s.e));
		}
		
		memset(dp, -1, sizeof(dp));

		INT64 result = FREELANCER(maxE);

		printf("#%d %lld\n", t, result);
	}
	
	
}