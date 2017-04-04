/*
 * 키재기
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

#define DEBUG
#define MAX_N  300007
#define MAX_Q  300007

struct query {
  int from, to;
  int height;
};

typedef int T;

struct tnode {
    T key;
    int priority;
    int size;
    tnode *left, *right;

    tnode(const T& key_) : key(key_), priority(rand()), size(1), left(NULL), right(NULL) {}
    void setleft(tnode* node_) { left = node_; adjustsize(); }
    void setright(tnode* node_) { right = node_; adjustsize(); }
    void adjustsize() {
      size = 1;
      if (left) size += left->size;
      if (right) size += right->size;
    }
};

typedef pair<tnode*, tnode*> nodepp;

nodepp split(tnode* root, const T& key) {
    if (root == NULL) return nodepp(NULL, NULL);
    if (root->key < key) {
      nodepp rs = split(root->right, key);
      root->setright(rs.first);
      return nodepp(root, rs.second);
    }
    nodepp ls = split(root->left, key);
    root->setleft(ls.second);
    return nodepp(ls.first, root);
}

tnode* insert(tnode* root, tnode* t) {
  if (root == NULL) return t;
  if (root->priority < t->priority) {
    nodepp ss = split(root, t->key);
    t->setleft(ss.first);
    t->setright(ss.second);
    return t;
  }
  else if (t->key < root->key){
    root->setleft(insert(root->left, t));
  }
  else {
    root->setright(insert(root->right, t));
  }
  return root;
}

tnode* insert(tnode* root, const T& t) {
  return insert(root, new tnode(t));
}

void nodefree(tnode* root)
{
  if (root) {
    nodefree(root->left);
    nodefree(root->right);
    free(root);
  }
}

template <typename T>
int countLT(tnode* root, T key) {
  if (root == NULL) return 0;
  if (root->key >= key)
    return countLT(root->left, key);
  int ls = (root->left ? root->left->size : 0);
  return ls + 1 + countLT(root->right, key);
}

int CASE;
int N, Q;
int A[MAX_N];
query QA[MAX_Q];
vector<pair<int, int> > qs[MAX_N];
tnode *root;

int main()
{
#ifdef DEBUG
  freopen("input/input1.txt", "r", stdin);
  freopen("output/result.txt", "w", stdout);
#endif
  scanf("%d", &CASE);
  for (int t = 1; t <= CASE; ++t) {
    scanf("%d %d", &N, &Q);
    for (int i = 1; i <= N; ++i) {
      scanf("%d", A+i);
    }

    for (int i = 1; i <= Q; ++i) {
      query& q = QA[i];
      scanf("%d %d %d", &q.from, &q.to, &q.height);
      qs[q.from].push_back(pair<int,int>(q.height, 0));
      qs[q.to+1].push_back(pair<int,int>(q.height, 0));
    }

    /* build tnode */
    root = NULL;
    for (int i = 1; i <= N; ++i) {
      root = insert(root, new tnode(A[i]));
      for (int j = 0; j < qs[i].size(); ++j) {
        qs[i][j].second = countLT(root, qs[i][j].first);
      }
    }

    /* generate query answer */
    for (int i = 1; i <= Q; ++i) {
      query& q = QA[i];
      int left, right;

      for (int j = 0; j < qs[q.from].size(); j++)
        if (qs[q.from][j].first == q.height) {
          left = qs[q.from][j].second;
          break;
        }

      for (int j = 0; j < qs[q.to+1].size(); j++)
        if (qs[q.to+1][j].first == q.height) {
          right = qs[q.to+1][j].second;
          break;
        }
      printf("%d\n", right - left);
    }

    /* free */
    nodefree(root);
    for (int i = 1; i <= N; ++i)
      qs[i].clear();
  }
}
