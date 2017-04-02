/* 
 * 가장많은 수
 * 탐색: 가장 많이 발견된 수 
 *
 --
 --
 정렬후 number counting -> 최대값중 해당 숫자가 작은 값 
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <map>
#include <algorithm>

#define DEBUG

using namespace std;

typedef long long INT64;
const int MAX_N = 1000000;
int N;

int A[MAX_N + 9];
multimap<int, int> frequency;

int NUMBER_COUNT()
{
	int value, count;
	int max_count;

	value = A[1];
	count = 1;
	max_count = 0;
	for (int i = 2; i <= N; ++i)
	{
		if (A[i] == value)
			count++;
		else
		{
			frequency.insert(pair<int, int>(count, value));
			max_count = max(count, max_count);
			value = A[i];
			count = 1;
		}
	}

	frequency.insert(pair<int, int>(count, value));
	max_count = max(count, max_count);

	pair<multimap<int, int>::iterator, multimap<int, int>::iterator> iterPair = frequency.equal_range(max_count);

	int min_result = 100000000;

	for (multimap<int, int>::iterator iter = iterPair.first; iter != iterPair.second; ++iter)
	{
		min_result = min(min_result, iter->second);
	}

	return min_result;

}

int main()
{
#ifdef DEBUG
	freopen("C:\\temp\\number_count.txt", "r", stdin);
	freopen("C:\\temp\\result.txt", "w", stdout);
#endif
	scanf("%d", &N);
	for (int i = 1; i <= N; ++i) {
		scanf("%d", A + i);
	}

	sort(A + 1, A + N + 1);

	int result = NUMBER_COUNT();
	printf("%d\n", result);
	return 0;
}
