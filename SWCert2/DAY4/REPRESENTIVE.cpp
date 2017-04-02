/* 
 * 구간 대표값 
 *    (합/최대/최소): RMQ 
 *
 --
 --
 */

#define _SCL_SECURE_NO_WARNINGS

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <queue>
#include <functional>
#include <algorithm>

/*
첫 번째 줄에 정수의 개수 N이 주어진다. (1 ≤ N ≤ 100, 000)

두 번째 줄에 질이의 개수 Q가 주어진다. (1 ≤ Q ≤ 200, 000)

세 번째 줄부터 Q개의 줄에 걸쳐 질의의 정보가 주어진다.각 질의는 다음 형태로 이루어진다.

0 x y : x번째 수를 y로 변경한다. (1 ≤ x ≤ N, -100, 000 ≤ y ≤ 100, 000)
1 x y : x번째 수부터 y번째 수까지의 합을 구한다. (1 ≤ x ≤ y ≤ N)
*/

using namespace std;

#define DEBUG 

const int MAX_N = 1000000;
typedef long long INT64;

struct represent {
	INT64 mi, ma, sum;
};

class BIT {
	int N;
	int IdxSize;

	represent tree[MAX_N * 4];	/* 최대 4 배 */

public:
	BIT()
	{
		N = 0;

		for (int i = 0; i < (4 * MAX_N); ++i) {
			tree[i].mi = 987654321ll;
			tree[i].ma = -987654321ll;
			tree[i].sum = 0ll;
		}
	}

	void setup(int arr[], int arrsize)
	{
		N = arrsize;
		for (IdxSize = 1; IdxSize < N; IdxSize *= 2)
			;

		for (int i = 0; i < arrsize; ++i) {
			tree[IdxSize + i].mi = (INT64)arr[i];
			tree[IdxSize + i].ma = (INT64)arr[i];
			tree[IdxSize + i].sum = (INT64)arr[i];
		}
			

		(void)init(1);
	}

	void update(int idx, int value)
	{
		tree[IdxSize + idx].mi = (INT64)value;
		tree[IdxSize + idx].ma = (INT64)value;
		tree[IdxSize + idx].sum = (INT64)value;
		updateIndex((IdxSize + idx) >> 1);
	}

	represent query(int from, int to)
	{
		represent result;
		return result = queryInternal(from, to, 1, 0, IdxSize - 1);
	}
private:
	int init(int pos)
	{
		if (pos >= IdxSize) return pos;

		int leftIndex = init(pos * 2);
		int rightIndex = init(pos * 2 + 1);

		tree[pos].sum = tree[leftIndex].sum + tree[rightIndex].sum;
		tree[pos].mi = min(tree[leftIndex].mi, tree[rightIndex].mi);
		tree[pos].ma = max(tree[leftIndex].ma, tree[rightIndex].ma);

		return pos;
	}

	void updateIndex(int pos)
	{
		if (pos > 0) {
			tree[pos].sum = tree[pos * 2].sum + tree[pos * 2 + 1].sum;
			tree[pos].mi = min(tree[pos * 2].mi, tree[pos * 2 + 1].mi);
			tree[pos].ma = max(tree[pos * 2].ma, tree[pos * 2 + 1].ma);
			updateIndex(pos >> 1);
		}
	}

	represent queryInternal(int left, int right, int IndexNode, int IndexLeft, int IndexRight)
	{
		represent result;

		if (right < IndexLeft || IndexRight < left)
			return tree[0];

		if (left <= IndexLeft && IndexRight <= right)
			return tree[IndexNode];

		int mid = (IndexLeft + IndexRight) / 2;

		represent left_rep = queryInternal(left, right, IndexNode * 2, IndexLeft, mid);
		represent right_rep = queryInternal(left, right, IndexNode * 2 + 1, mid + 1, IndexRight);

		result.ma = max(left_rep.ma, right_rep.ma);
		result.mi = min(left_rep.mi, right_rep.mi);
		result.sum = left_rep.sum + right_rep.sum;

		return result;
	}
};

int N, Q;

int A[MAX_N + 9];

BIT bit;

void RANGE(int a, int b)
{
	represent result = bit.query(a - 1, b - 1);

	printf("%lld %lld %lld\n", result.mi, result.ma, result.sum);
}

int main()
{
#ifdef DEBUG
	freopen("C:\\temp\\representitive.txt", "r", stdin);
	freopen("C:\\temp\\result.txt", "w", stdout);
#endif
	scanf("%d", &N);

	for (int i = 1; i <= N; ++i)
	{
		scanf("%d", A + i);
	}

	bit.setup(A + 1, N);

	scanf("%d", &Q);

	for (int i = 1; i <= Q; ++i) {
		int a, b;

		scanf("%d %d", &a, &b);
		RANGE(a, b);
	}
}
