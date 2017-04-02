/* 탐욕 */

/* 
첫째 줄에 N과 K가 주어진다. (1 ≤ N, K ≤ 300,000)

다음 N개 줄에는 각 보석의 정보 Mi와 Vi가 주어진다. (1 ≤ Mi, Vi ≤ 1,000,000)

다음 K개 줄에는 가방에 담을 수 있는 최대 무게 Ci가 주어진다. (1 ≤ Ci ≤ 100,000,000)

모든 숫자는 양의 정수이다.

*/

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <queue>
#include <algorithm>

using namespace std;

#define DEBUG 

typedef long long INT64;
typedef pair<int, int> intpair;

const int MAX_N = 300000;

int N, K;

intpair A[MAX_N + 9];
int     C[MAX_N + 9];
int     choose[MAX_N + 9];
priority_queue<int > pq;

// bool cmp(const intpair& a, intpair& b) { return (a.first < b.first);  }

int main()
{
#ifdef DEBUG
	freopen("C:\\temp\\jwoul.txt", "r", stdin);
	freopen("C:\\temp\\result.txt", "w", stdout);
#endif

	scanf("%d %d", &N, &K);
	for (int i = 1; i <= N; ++i)
		scanf("%d %d", &A[i].first, &A[i].second);

	for (int i = 1; i <= K; ++i)
		scanf("%d", C + i);

	sort(A + 1, A + N + 1);
	sort(C + 1, C + K + 1);

	INT64 sum = 0;

	memset(choose, 0, sizeof(choose));
	for (int i = 1, j = 1; i <= K; ++i) {
		/* C[i] 무게를 넣을 수 있는 보석들을 priority_queue에 집어 넣는다... 무게 정보는 생략 (이미 모두 특정 무게를 넘기 때문에 불필요) */
		for (; j <= N && A[j].first <= C[i] ; j++)
			pq.push(A[j].second);

		if (!pq.empty())
		{
			int mv = pq.top(); pq.pop();
#ifdef DEBUG
			printf("%5d->[%d]\n", i, mv);
#endif
			sum += (INT64) mv;
		}
	}

	printf("%lld\n", sum);
	return 0;
}