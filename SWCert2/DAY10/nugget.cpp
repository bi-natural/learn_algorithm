/*
 * 너겟
 * 
 --
 태양이는 N개의 너겟 상자를 가지고 있다. i번째 너겟 상자에는 Ai개의 너겟이 들어있다.

명우는 태양이에게 정확히 x개의 너겟을 달라고 부탁하는데, 태양이는 가지고 있는 너겟 상자 중 
일부를 선택해 명우에게 전달한다.

태양이가 가지고 있는 너겟 상자에 있는 너겟 개수에 따라, 명우에게 전달할 수 없는 너겟 갯수가 
있을 수 있다. 예를 들어, 태양이가 가지고 있는 너겟 상자의 개수는 3개고, 각 상자에 너겟이 
1개, 2개, 5개 있다면, 명우에게 4개의 너겟을 전달할 방법이 없다.

심술궂은 명우는 태양이를 당황시키려고 한다. 명우를 도와 전달할 수 없는 너겟 갯수 중에 
가장 작은 값을 구하는 프로그램을 작성하시오.
 --
 */
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>

#define DEBUG
#define MAX_N 100007

using namespace std;

typedef long long INT64;
typedef pair<int, int> PPI;

int CASE; 
int N;
INT64 A[MAX_N];
INT64 ASUM[MAX_N];
INT64 B[MAX_N];

/*
 * A[i] : 정렬된 입력 숫자값 
 *
 * Mi   : 지금껏 i-1번째 숫자까지 활용하여 1..부터 시작해서 가장 크게 만들수 있는 최대 숫자값 
 *
 * 새로 보게되는 숫자 A[i]에 대해서 
 *     A[i]를 사용해서 만들게 되는 새로운 숫자는 (A[i] + 1..Mi) 이고 여기서 최소값은 A[i] + 1 
 *     A[i]를 사용하지 않고 만들수 있는 숫자 범위는 앞서 구한 (1..Mi)
 *
 *     --> 결국은 새롭게 표현할 수 있는 숫자 범위는 (1 .. Mi) , (A[i]+1 .. A[i]+Mi)
 *     --> Mi+1 != A[i]+1 이 아니라면  (Mi+1 ~ A[i]-1) 사이의 값은 표현할 수 없음.
 * 
 */
INT64 NUGGET()
{
	INT64 Mi = 0ll; 
	
	for (int i = 1; i <= N; ++i) {
		if (A[i] > Mi+1) 
			break;
		Mi = Mi + A[i];
	}
	
	return Mi + 1;
}

int main()
{
#ifdef DEBUG
	freopen("C:\\temp\\nugget.txt", "r", stdin);
	freopen("C:\\temp\\result.txt", "w", stdout);
#endif	

	scanf("%d", &N);
	
	for (int i = 1; i <= N; ++i)
		scanf("%lld", A+i);
		
	sort(A+1, A+1+N);
	
#ifdef DEBUG
	printf(" A = ");
	for (int i = 1; i <= N; ++i) 
		printf("%3d", A[i]);
	printf("\n");
#endif	
	INT64 result = NUGGET();
	
	printf("%lld\n", result);
	return 0;
}

