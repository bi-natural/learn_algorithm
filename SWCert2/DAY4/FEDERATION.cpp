/*
 * 동맹의 동맹은 동맹 
--
첫 번째 줄에 낙성마을의 사람의 수 N이 주어진다. (1 ≤ N ≤ 100,000)

두 번째 줄에 질의의 수 Q가 주어진다. (1 ≤ Q ≤ 200,000)

세 번째 줄부터 Q개의 줄에 걸쳐 질의가 주어진다. 각 질의는 다음의 형태 중 하나로 주어진다. (1 ≤ a, b ≤ N)

0 a b : a번 사람과 b번 사람이 동맹 관계를 맺었음을 의미하는 질의이다.
1 a b : a번 사람과 b번 사람이 동맹 관계에 있는지 물어보는 질의이다.
--

  union-find set를 사용하여 체크 
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <map>
#include <algorithm>

using namespace std;

#define DEBUG 

const int MAX_N = 100000;
const int MAX_Q = 200000;

int N, Q;

int UF[MAX_N + 9];

int ufind(int a)
{
	if (UF[a] == a)
		return a;
	else
		return UF[a] = ufind(UF[a]);
}

void ufset(int a, int b)
{
	a = ufind(a);
	b = ufind(b);
	if (a != b)
		UF[a] = b;
}

int ufederation(int a, int b)
{
	return (ufind(a) == ufind(b)) ? 1 : 0;
}

void QUERY(int q, int a, int b)
{
	if (q == 0) {
		/* set uf (a, b) */
		ufset(a, b);
	}
	else
	{
		printf("%d\n", ufederation(a, b));
	}
}

int main()
{
#ifdef DEBUG
	freopen("C:\\temp\\federation.txt", "r", stdin);
	freopen("C:\\temp\\result.txt", "w", stdout);
#endif
	scanf("%d %d", &N, &Q);

	for (int i = 1; i <= N; i++) {
		UF[i] = i;
	}

	for (int i = 1; i <= Q; ++i) {
		int q, a, b;

		scanf("%d %d %d", &q, &a, &b);

		QUERY(q, a, b);
	}
}
