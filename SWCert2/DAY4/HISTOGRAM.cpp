/* 
 * 히스토그램에서 가장 큰 직사각형
 * 
 * 자료구조: 히스토그램 
 --
입력은 여러 개의 테스트케이스로 이루어져 있다. 각 테스트케이스의 첫 정수는 직사각형의 수N을 의미한다
( 1 ≤ N ≤ 100 , 000 ) (1≤N≤100,000). 만약 N = 0 N=0이면 입력의 끝을 의미한다.
같은 줄에 N개의 정수가 공백을 사이에 두고 주어진다. 이는 순서대로 직사각형
N개의 높이를 나타낸다. 주어지는 높이는1,000,000,000 보다 크지 않다.
 --
 <풀이>
  
D[i]로 끝나는 최대 사각형들의 넓이를 계산한다.
D[i]는 앞에 자기보다 작은 최소 사각형까지를 고려한 합 중 최대 값.
  이를 위해 stack에 remaining_top를 유지한다. 
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <stack>
#include <functional>
#include <algorithm>

using namespace std;

#define DEBUG 

const int MAX_N = 100000;
const int MAX_H = 1000000000;
typedef long long INT64;

int N;

INT64 A[MAX_N + 9];

INT64 HISTOGRAM()
{
	INT64 ret = 0;

	stack<pair<INT64, INT64> > st;

	st.push(pair<INT64, INT64>(0, 0));

	for (int i = 1; i <= N; ++i) {
		while (!st.empty()) {
			pair<INT64, INT64>& top = st.top();

			if (A[i] <= top.second) {
				st.pop();
			}
			else 
			{
				ret = max(ret, A[i] * (i - top.first));
				st.push(pair<INT64, INT64>((INT64) i-1, A[i]));
				break;
			}
		}
	}
	return ret;
}

int main()
{
#ifdef DEBUG
	freopen("C:\\temp\\histogram.txt", "r", stdin);
	freopen("C:\\temp\\result.txt", "w", stdout);
#endif
	for (;;)
	{
		scanf("%d", &N);

		if (N == 0)
			break;

		for (int i = 1; i <= N; ++i)
		{
			scanf("%lld", A + i);
		}

		INT64 result = HISTOGRAM();

		printf("%lld\n", result);

	}
	

}

