/* 
 * pro pre-test for Oct
 */

#include <stdio.h>

using namespace std;

const int max_nodes = 10000;
const int max_length = 10000;

enum node_type {
    none = 0,
    fuse = 1,
    explosive = 2,
    y_split = 3
};

struct node {
    int a, b, c;
    ndoe_type t;
    graph* node[2];
};

struct node *graph;

int T;  // number of test case 
int N;  // number of nodes

int main()
{
    freopen('testinput.txt', "r", stdin);

    cin << T;
    
}