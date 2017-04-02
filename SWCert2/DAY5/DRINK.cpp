/* 술약속 */

#include <cstdio>
#include <cstdlib>
#include <queue>
#include <algorithm>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

#define DEBUG

using namespace std;

typedef long long INT64;
struct schedule {
	int t;
	int d;
};

const int MAX_N = 100000;
int N;
schedule A[MAX_N + 9];

/*
* 모든 t1/d1 에 대해 정렬하여 t1/d1 으로 역정렬 (시간이 제일 오래걸리고, 벌주는 조금주는데를 먼저 간다.
*
*      T2*D1 < T1*D2
*
* 전체 계산은 2  * Sigma{i = 1, N} (T1..TN)*DN
*/

bool fk(const schedule& a, const schedule& b)
{
	return (b.t * a.d < a.t * b.d);
}

int DRINK()
{
	sort(A + 1, A + N + 1, fk);

#ifdef DEBUG
	for (int i = 1; i <= N; ++i) {
		printf("(%d,%d)=%.5f", A[i].t, A[i].d, (double) A[i].t / (double)(A[i].d));
	}
	printf("\n");
#endif
	int tsum = 0;
	int result = 0;
	for (int i = 1; i <= N; ++i) {
		tsum += A[i].t;
		result = 2 * tsum * A[i].d;
	}
	return result;
}

int main(int argc, char** argv)
{
#ifdef DEBUG
	freopen("C:\\temp\\drink.txt", "r", stdin);
	freopen("C:\\temp\\result.txt", "w", stdout);
#endif

	scanf("%d", &N);

	for (int i = 1; i <= N; ++i) {
		schedule& s = A[i];
		scanf("%d", &s.t, &s.d);
	}

	int result = DRINK();
	printf("%d\n", result);

	return 0;
}