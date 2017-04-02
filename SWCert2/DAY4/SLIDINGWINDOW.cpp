/* 
 * 슬라이딩 윈도우 
 * 
 --
 첫 줄에 배열의 크기 N과 부분배열의 크기 K가 주어진다. (1 ≤ K ≤ N ≤ 1,000,000)

 둘째 줄에 배열의 내용을 나타내는 N개의 정수들이 공백으로 구분되어 주어진다. 
 주어지는 수는 절대값이 1,000,000,000 보다 크지 않다.
 --
 
 길이가 N인 부분배열에 대한 (최대, 최소, 합)을 구함. 
 (ex. 길이가 임의로 주어지고 Query가 주어지면 Indexed Tree사용해야 함.)
 
 최대/최소시 out-of-range된 것들을 쉽게 체크하기 위한 알고리즘 필요. 
 
 최대/최소를 구하기 위해서는 deqeue를 사용한다.
 	앞위로 넣기: push_front, push_back
 	앞뒤에서 빼기: pop_front, pop_front
 	값 참조: front, back
  
 */
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <deque>
#include <algorithm>

using namespace std;

#define DEBUG 

const int MAX_N = 1000000;

int N, K;
int A[MAX_N + 9];

deque<pair<int, int> > minq;
deque<pair<int, int> > maxq;

struct RESULT {
	int mi, ma, sum;
} RESULTS[MAX_N + 9];

void SSUM(int idx, int value)
{
	if (idx <= K)
	{
		RESULTS[1].sum += value;
	}
	else
	{
		RESULTS[1 + idx - K].sum = RESULTS[idx - K].sum + value - A[idx - K];
	}
}

void SMIN(int idx, int value)
{
	if (!minq.empty())
	{
		pair<int, int> front = minq.front();

		if (front.first <= (idx - K))
			minq.pop_front();

		while (!minq.empty()) {
			pair<int, int> back = minq.back();

			if (value < back.second)
				minq.pop_back();
			else
				break;
		}
	}

	minq.push_back(pair<int, int>(idx, value));
	
	pair<int, int> current_front = minq.front();

	if (idx <= K)
	{
		RESULTS[1].mi = current_front.second;
	}
	else
	{
		RESULTS[1 + idx - K].mi = current_front.second;
	}
}

void SMAX(int idx, int value)
{
	if (!maxq.empty())
	{
		pair<int, int> front = maxq.front();

		if (front.first <= (idx - K))
			maxq.pop_front();

		while (!maxq.empty()) {
			pair<int, int> back = maxq.back();

			if (value > back.second)
				maxq.pop_back();
			else
				break;
		}
	}

	maxq.push_back(pair<int, int>(idx, value));

	pair<int, int> current_front = maxq.front();

	if (idx <= K)
	{
		RESULTS[1].ma = current_front.second;
	}
	else
	{
		RESULTS[1 + idx - K].ma = current_front.second;
	}
}

int main()
{
#ifdef DEBUG
	freopen("C:\\temp\\slidingwindow.txt", "r", stdin);
	freopen("C:\\temp\\result.txt", "w", stdout);
#endif
	scanf("%d %d", &N, &K);

	for (int i = 1; i <= N; i++) {
		scanf("%d", A + i);

		SSUM(i, A[i]);
		SMIN(i, A[i]);
		SMAX(i, A[i]);
	}

	for (int i = 1; i <= N - K + 1; ++i) {
		printf("%d %d %d\n", RESULTS[i].mi, RESULTS[i].ma, RESULTS[i].sum);
	}

	return 0;
}
