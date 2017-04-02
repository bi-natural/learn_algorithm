/* 
 * DP: 다리건너기 
 --
 -- 
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <map>
#include <algorithm>

using namespace std;

#define DEBUG 

const int MAX_SPELLS = 20;
const int MAX_CHARS = 100;
 
char SPELL[MAX_SPELLS + 9]; int SN;
char A[2][MAX_CHARS + 9]; int AN;

multimap<char, int> MAP[2];

int dp[MAX_SPELLS + 9][MAX_CHARS + 9][2];

int BRIDGE(int s, int pos, int b)
{
	int& ref = dp[s][pos][b];

	if (ref != -1)
		return ref;


	/* 기저값 : 모든 주문을 다 썼음. */
	if (s > SN) {
#ifdef DEBUG
		printf("!!! use all spell. s=%d, pos=%d, b=%d\n", s, pos, b);
#endif
		return ref = 1;	/* 완료된 케이스 */
	}

	/* 현재 주문문자 처리 */
	char ch = SPELL[s];

	ref = 0;
	
	/* 교차한 다리의 주문문자(들) 처리 */
	int switch_b = b ^ 1;
	
	pair<multimap<char, int>::iterator, multimap<char, int>::iterator> iterPair = MAP[switch_b].equal_range(ch);
#ifdef DEBUG
	printf("!current_spell = %c ... find at A[%d]\n", ch, switch_b);
#endif
	for (multimap<char, int>::iterator iter = iterPair.first; iter != iterPair.second; ++iter)
	{
		int& next_pos = iter->second;
#ifdef DEBUG
		printf("!current_spell = %c, -> next_pos : A[%d][%d] = %c\n", ch, switch_b, next_pos, A[switch_b][next_pos]);
#endif
		if (next_pos > pos)
		{
			ref += BRIDGE(s + 1, next_pos, switch_b);
		}
	}
#ifdef DEBUG
	printf("!dp[%d][%d][%d] = %d\n", s, pos, b, ref);
#endif
	return ref;
}

int main()
{
#ifdef DEBUG
	freopen("C:\\temp\\bridge2.txt", "r", stdin);
	freopen("C:\\temp\\result.txt", "w", stdout);
#endif
	scanf("%s\n", &SPELL[1]); SN = strlen(&SPELL[1]);
	scanf("%s\n", &A[0][1]); AN = strlen(&A[0][1]);
	scanf("%s\n", &A[1][1]); 

	memset(dp, -1, sizeof(dp));

	MAP[0].clear(); MAP[1].clear();
	for (int i = 1; i <= AN; ++i) {
		MAP[0].insert(pair<char, int>(A[0][i], i));
		MAP[1].insert(pair<char, int>(A[1][i], i));
	}

	int result1 = BRIDGE(1, 0, 0); /* 0번 다리, 0번 포지션에서 첫 (SPELL) 출발하는 경우 */
	int result2 = BRIDGE(1, 0, 1); /* 1번 다리, 0번 포지션에서 첫 (SPELL) 출발하는 경우 */

#ifdef DEBUG
	for (int i = 0; i < 2; i++) {
		for (int i = 1; i <= AN; ++i) {
			printf("%3d", dp[1][i][i]);
		}
		printf("\n");
	}
#endif
	printf("%d\n", result1 + result2);

}
