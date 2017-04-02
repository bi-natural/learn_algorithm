/*
 * 집합판별
 *
 --
Set::=
Set          ::= "{" Elementlist "}"
Elementlist  ::= < empty > | List
List         ::= Element | Element "," List
Element      ::= Atom | Set
Atom         ::= "{" | "}" | ","
 -- 
 */
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>

#define DEBUG
#define MAX_N 100007

using namespace std;

typedef long long INT64;
typedef pair<int, int> BOX;

int CASE; 
int N;
char A[MAX_N];

enum STATE {
	NONE,
	SET,
	ELEMENT_LIST,
	LIST,
	SUBLIST,
	ELEMENT,
	ATOM
};

stack<char> st;

int check(int s, int e, STATE state)
{
	int ret ;
	
	switch(state) {
	case SET:
		if (A[s] == '{' && A[e] == '}') 
			return check(s+1, e-1, ELEMENT_LIST);
		return 0;
		
	case ELEMENT_LIST:
		if (s > e) 
			return s;
		return check(s, e, LIST);
		
	case LIST:
		if (check(s, e, ELEMENT))
			return e;
			
		for (int ei = s+1; ei <= e; ++ei) 
			if (check(s, ei, ELEMENT) && A[ei+1] == ',' && check(ei+2, e, LIST)) {
				return e;
			}
		return 0;
							
	case ELEMENT:
		if (check(s, e, ATOM) || check(s, e, SET))
			return e;
		return 0;
		
	case ATOM:
		if (s == e && (A[s] == '{' || A[s] == '}' || A[s] == ','))
			return e;
		return 0;
		
	default:
		return 0;
	}
}

int main()
{
#ifdef DEBUG
	freopen("C:\\temp\\isitset.txt", "r", stdin);
	freopen("C:\\temp\\result.txt", "w", stdout);
#endif	

	scanf("%d", &N);
	for (int i = 1; i <= N; ++i) {
		scanf("%s", A+1);
		N = strlen(A+1);
	
		int result = check(1, N, SET);
		printf("Word #%d: %s\n", i, result ? "Set" : "No Set");
	}
	
	return 0;
}

