/* 
 * 자료구조: Heap --> Median 
 *
--
첫 번째 줄에 주어지는 정수의 개수 N이 주어진다. (1 ≤ N ≤ 99,999, N은 홀수)

두 번째 줄부터 N개의 줄에 걸쳐 각 줄에 하나씩 정수가 주어진다. (1 ≤ 주어지는 정수 ≤ 1,000,000,000)
--
 
<풀이> 
 중앙값을 연속해서 갖고 있음. priority_queue를 사용한다.
 
 2개의 priority_queue를 사용
    - max heap (작은 값들중 가장 최대를 리턴) 
	- min heap (큰 값들중에 가장 최소를 리턴)
	
 입력 들어오는 것에 대해 무조건 max heap에 넣고 대소비교를 통해 re-arrange한다. 
  
 */
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <queue>
#include <functional>
#include <algorithm>

using namespace std;

#define DEBUG 

const int MAX_N = 1000000;

#if 0
template <typename T>
class heap {
	heap() : size(0) {}
	void insert(<T> a) 
	{
		tree[++size] = a;
		
		for (int pos = size; (pos / 2) > 0 && tree[pos] < tree[pos / 2]; pos /= 2)
			swap(tree[pos / 2], tree[pos]);
	}
	<T> top() { return tree[1]; }
	<T> peek()
	{
		swap(tree[1], tree[size]);
		size--;

		for (int pos = 1; (pos * 2 <= size); pos *= 2)
		{

		}
	}
private: 
	int size;
	<T> tree;
};
#endif 

int N;

int main()
{
#ifdef DEBUG
	freopen("C:\\temp\\median.txt", "r", stdin);
	freopen("C:\\temp\\result.txt", "w", stdout);
#endif

	priority_queue<int, vector<int>, greater<int> > left_q;
	priority_queue<int, vector<int>, less<int> > right_q;

	scanf("%d", &N);
	for (int i = 1, a; i <= N; ++i) {
		int left_qsize = left_q.size();
		int right_qsize = right_q.size();
		
		scanf("%d", &a);

		if (left_qsize == right_qsize)
			left_q.push(a);
		else
			right_q.push(a);

		if (!left_q.empty() && !right_q.empty() && left_q.top() < right_q.top())
		{
			int left_top = left_q.top();  left_q.pop();
			int right_top = right_q.top(); right_q.pop();

			right_q.push(left_top);
			left_q.push(right_top);
		}

		if (i % 2)
			printf("%d\n", left_q.top());
	}
	return 0;
}
