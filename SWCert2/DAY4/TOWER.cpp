/* 
 * 탑 
 *    스택: 타워와 레이저 
--
첫 번째 줄에 탑의 수 N이 주어진다. (1 ≤ N ≤ 500,000)

두 번째 줄에 N개의 탑들의 높이가 직선상에 놓인 순서대로 하나의 빈칸을 사이에 두고 각각 주어진다. 
(1 ≤ 탑의 높이 ≤ 100,000,000)
--

 스택을 이용하여 (고려할) 필요가 없어진 것들은 스택에서 제거하면서 확인
  
 */
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <stack>
#include <algorithm>

using namespace std;

#define DEBUG 

const int MAX_N = 500000;
const int MAX_H = 10000000;

int N;
int A[MAX_H+9];
int B[MAX_H + 9];

void TOWER()
{
	stack< pair<int, int> > st;

	for (int i = 1; i <= N; ++i) {
		while (! st.empty())
		{
			pair<int, int> top = st.top();

			if (top.first >= A[i]) {
				B[i] = top.second;
				st.push(pair<int, int>(A[i], i));
				break;
			}
			else {
				st.pop();
			}
		}

		if (st.empty()) {
			st.push(pair<int, int>(A[i], i));
			B[i] = 0;
		}
	}
}

int main()
{
#ifdef DEBUG
	freopen("C:\\temp\\tower.txt", "r", stdin);
	freopen("C:\\temp\\result.txt", "w", stdout);
#endif
	scanf("%d", &N);

	for (int i = 1; i <= N; i++) {
		scanf("%d", A + i);
	}

	memset(B, 0, sizeof(B));

	TOWER();

	for (int i = 1; i <= N; ++i)
		printf("%d ", B[i]);
	printf("\n");
}
