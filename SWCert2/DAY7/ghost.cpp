/*
 * 유령선 
 *
 --
첫 번째줄에 두 정수 W 와 H가 공백을 사이에 두고 주어진다. (2≤W,H≤1500)
두 번째 줄부터 H줄에 걸쳐 각 줄에 W개의 문자가 주어진다.

각 문자는 X, O, S, E 중 하나며 전체 문자들 중 S와 E는 정확히 하나임이 보장된다.

X는 처음부터 부서진 판자를 나타낸다.
O는 강희가 밟고 지나갈 수 있지만, 밟은 이후 부서지는 판자를 나타낸다.
S는 처음 강희가 서 있는 판자의 위치를 나타낸다.
E는 유령선의 구명보트 위치를 나타낸다.
 --
 
그래프로 생각해서 BFS를 사용한다. 
 */
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>

#define DEBUG

using namespace std;

typedef long long INT64;
typedef pair<int, int> BOX;

const int MAX_N = 1500;

int H, W;

char board[MAX_N+9][MAX_N+9];
int  dist[MAX_N+9][MAX_N+9];

int GHOST()
{
	BOX s, e;
	
	/* find s,e & init dist */
	for (int i = 1; i <= H; ++i)
		for (int j = 1; j <= W; ++j) {
			dist[i][j] = -1;
			if (board[i][j] == 'S')
				s.first = i, s.second = j;
			else if (board[i][j] == 'E')
				e.first = i, e.second = j;
		}

#ifdef DEBUG
	printf(" H = %d, W = %d\n", H, W);
	printf(" found s = (%d, %d)\n", s.first, s.second);
	printf(" found e = (%d, %d)\n", e.first, e.second);
#endif
	/* find ways (BFS) */
	queue<BOX> q;
	
	dist[s.first][s.second] = 0;
	q.push(s);
	while (!q.empty()) {
		BOX top = q.front(); q.pop();
		vector<BOX> iter;
		
		iter.clear();
		if (top.first > 1) 
			iter.push_back(BOX(top.first-1, top.second));
		if (top.first < H)
			iter.push_back(BOX(top.first+1, top.second));
		if (top.second > 1)
			iter.push_back(BOX(top.first, top.second-1));
		if (top.second < W)
			iter.push_back(BOX(top.first, top.second+1));
			
		for (int i = 0; i < iter.size(); ++i) {
#ifdef DEBUG
			printf(" -- (%d, %d) )iteration : (%d, %d) state = '%c'\n", top.first, top.second, iter[i].first, iter[i].second, board[iter[i].first][iter[i].second]);
#endif			
			if (board[iter[i].first][iter[i].second] != 'X' && dist[iter[i].first][iter[i].second] == -1) {
				/* reachable, and not visited */
				dist[iter[i].first][iter[i].second] = 1 + dist[top.first][top.second];
				q.push(BOX(iter[i]));
			}
		}
	}
	
	return dist[e.first][e.second];
}

int main()
{
#ifdef DEBUG
	freopen("C:\\temp\\ghost.txt", "r", stdin);
	freopen("C:\\temp\\result.txt", "w", stdout);
#endif	
	scanf("%d %d", &W, &H);

	for (int i = 1; i <= H; ++i) {
		scanf("%s\n", &board[i][1]);
	}
		
#ifdef DEBUG
	for (int i = 1; i <= H; ++i)
		printf("%s\n", &board[i][1]);
#endif	

	int result = GHOST();
	printf("%d\n", result);
	return 0;
}
