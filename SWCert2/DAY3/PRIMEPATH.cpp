/* 
 * 탐색: 소수경로 
 --
 --
 
소수들을 구하고 해당 소수간에 DIFF가 1인 것들에 대해 가상으로 link가 있다고
가정하고 BFS를 구한다. 
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <map>
#include <vector>
#include <queue>
#include <algorithm>

#define DEBUG

using namespace std;

typedef long long INT64;
const int MAX_N = 1000000;
const int MAX_LIMIT = 10000;	/* 4자리 수 이하의 소수 */

int CASE, N;

bool isPrime[MAX_LIMIT];
vector<int> nPrimes;

struct node {
	int v;
	vector<int> adj;
};

vector<node> gPrimes;

bool diff_distance1(int a, int b)
{
	if (a < b)
		swap(a, b);

	int matched = 0;

	int aa = a;
	int bb = b;
	for (int i = 1; i <= 4; i++) {
		int ai = aa % 10; aa /= 10;
		int bi = bb % 10; bb /= 10;

		if (ai == bi)
			matched ++;
	}

	return (matched == 3);
}

void precalc()
{
	int MAX_LIMIT = 10000;

	for (int i = 2; i < MAX_LIMIT; ++i)
	{
		isPrime[i] = true;
	}

	for (int i = 2; i < MAX_LIMIT; ++i)
	{
		if (isPrime[i])
		{
			for (int j = 2 * i; j < MAX_LIMIT; j += i)
				isPrime[j] = false;
		}
	}

	for (int i = 1000; i <= 9999; ++i)
	{
		if (isPrime[i])
		{
			node n;

			n.v = i;
			n.adj.clear();
			gPrimes.push_back(n);

		}
	}

	/* 빌드 그래프 */
	for (int i = 0; i < gPrimes.size(); ++i)
		for (int j = i+1; j < gPrimes.size(); ++j)
		{
			if (diff_distance1(gPrimes[i].v, gPrimes[j].v))
			{
				gPrimes[i].adj.push_back(j);
				gPrimes[j].adj.push_back(i);
			}
		}
}

int findIndex(int a)
{
	int found = -1;

	for (int i = 0; i < gPrimes.size(); ++i)
	{
		if (a == gPrimes[i].v)
			return i;
	}
	return 0;
}

int isVisited[MAX_LIMIT+1];

/* Use bfs */
int bfs(int s, int e)
{
	memset(isVisited, 0, sizeof(isVisited));

	queue<int> q;

	q.push(s);
	isVisited[s] = 1;

	while (!q.empty())
	{
		int current_node = q.front();
		q.pop();

		if (current_node == e) {
			/* 경로 길이 */
			return isVisited[e] - isVisited[s];
		}

		for (int i = 0; i < gPrimes[current_node].adj.size(); ++i)
		{
			node& n = gPrimes[current_node];
			int& ni = n.adj[i];

			if (!isVisited[ni]) {
				isVisited[ni] = isVisited[current_node] + 1;
				q.push(ni);
			}
		}
	}
	return 0;
}

int bfs2(int s, int e)
{
	memset(isVisited, 0, sizeof(isVisited));

	queue<int> q;

	q.push(s);
	isVisited[s] = s;
	while (!q.empty())
	{
		int current_node = q.front();
		q.pop();

		if (current_node == e) {
			/* 경로 길이 */
			int length = 0;
#ifdef DEBUG
			printf("!found goal node (%d) at Idx(%d)\n", gPrimes[current_node].v, current_node);
#endif
			for (int i = current_node; i != s; i = isVisited[i])
			{
				length++;
#ifdef DEBUG
				printf("  - previous node (%d) at Idx(%d)\n", gPrimes[i].v, i);
#endif
			}
#ifdef DEBUG
			printf("!found start node (%d) at Idx(%d)\n", gPrimes[s].v, s);
#endif
			return length;
		}

		for (int i = 0; i < gPrimes[current_node].adj.size(); ++i)
		{
			node& n = gPrimes[current_node];

			int& ni = n.adj[i];
			if (!isVisited[ni]) {
				isVisited[ni] = current_node;	/* current_node에서 왔음. */
				q.push(ni);
			}
		}
	}
	return 0;
}

int PRIME_PATH(int a, int b)
{
	int nodeIdx_a = findIndex(a);
	int nodeIdx_b = findIndex(b);

	if (nodeIdx_a == 0 || nodeIdx_b == 0)
		return -1;

	return bfs2(nodeIdx_a, nodeIdx_b);
}

int main()
{
#ifdef DEBUG
	freopen("C:\\temp\\prime_path.txt", "r", stdin);
	freopen("C:\\temp\\result.txt", "w", stdout);
#endif
	scanf("%d", &CASE);

	precalc();

	for (int t = 1; t <= CASE; ++t)
	{
		int a, b;

		scanf("%d %d", &a, &b);

#ifdef DEBUG111
		printf("prime_path(%d, %d) = ", a, b);
#endif
		int result = PRIME_PATH(a, b);
#ifdef DEBUG111
		if (result > 0)
		{
			int i = b;
			printf("PATH = ");
			while (i != a)
			{
				printf("%5d", gPrimes[isVisited[i]].v);
				i = isVisited[i];
			}
			printf("\n");
		}
#endif
		printf("%d\n", result);
	}

}
