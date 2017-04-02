/* 풍선 
 *
 --
 큰 방에 N개의 풍선이 떠있다. 풍선들은 왼쪽부터 오른쪽까지 일렬로 있다. 
 진솔이는 화살 가지고 노는 것과 사냥 연습하는 것을 좋아한다. 진솔이는 화살을 왼쪽에서 오른쪽으로 쏜다.

높이는 임의로 선택한다. 화살은 선택된 높이 H에서 풍선을 마주칠 때까지 왼쪽에서 오른쪽으로 이동한다. 
화살이 풍선을 마주치는 순간, 풍선은 터지고 사라진다. 화살은 계속해서 가던길을 가는데 높이는 1 줄어든다. 
그러므로 만약 화살이 높이 H에서 이동 중이었다면 풍선을 터트린 후에는 높이가 H-1이 된다.

우리의 목표는 모든 풍선을 터트리되 가능한한 적은 화살을 사용하는 것이다.
<입력> 
첫 번째 줄에는 정수 N(1 ≤ N ≤ 1 000 000)이 들어온다.
두 번째 줄에는 배열 Hi가 N개 들어온다.
각각의 Hi(1 ≤ Hi ≤ 1 000 000)는 i번째 풍선의 높이에 해당하며 왼쪽에서 오른쪽으로 나열되는 순서이다.
 --
<풀이> 

아이디어: 높이 별로 쏜 화살의 개수를 기록한다.
 
1. 왼쪽 풍선 맞춘다. (높이 h)
2. 풍선을 맞추면 해당 h-1 높이에 화살이 떠 있다.
3. 다음 풍선의 높이를 봤는데 이미 해당 높이에 화살이 떠 있으면, 그 화살로 맞췄다고 가정하고 h-1 만큼 감소
4. 계속 동작하고 끝에 남아있는 높이의 화살을 다 더하면 최종화살개수 
 */


#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <map>
#include <algorithm>

using namespace std;

#define DEBUG 

const int MAX_N = 1000000;

int N;

int A[MAX_N + 9];
int B[MAX_N + 9];

int COUNT()
{
	int count = 0;

	for (int i = 1; i <= N; ++i)
		count += B[i];

	return count;
}

int main()
{
#ifdef DEBUG
	freopen("C:\\temp\\bolloon.txt", "r", stdin);
	freopen("C:\\temp\\result.txt", "w", stdout);
#endif

	scanf("%d", &N);

	memset(B, 0, sizeof(B));
	
	for (int i = 1; i <= N; ++i)
	{
		scanf("%d", A + i);

		if (B[A[i] + 1] > 0)
		{
			B[A[i] + 1] --;
		}
		B[A[i]] ++;
	}

	printf("%d\n", COUNT());
}
