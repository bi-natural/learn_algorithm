#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

typedef int KeyType;
struct node {
    KeyType key;
    int priority, size;

    node *left, *right;

    node(const KeyType& k) : key(k), priority(rand()), size(1), left(NULL), right(NULL) {};

    void setLeft(node *n) { left = n; updateSize(); }
    void setRight(node *n) { right = n; updateSize(); }

    void updateSize() {
        size = 1;
        if (left) size += left->size;
        if (right) size += right->size;
    }
};

typedef pair<node*, node*> NodePair;

NodePair split(node *root, KeyType k) {
    if (root == NULL) return NodePair(NULL, NULL);

    if (root->key < k) {
        NodePair rs = split(root->right, k);
        root->setRight(rs.first);
        return NodePair(root, rs.second);
    }

    NodePair ls = split(root->left, k);
    root->setLeft(ls.second);
    return NodePair(ls.first, root);
}

node *insert(node *root, node *n) {
    if (root == NULL) return n;

    // heap condition: parent's priority higher then children.
    if (root->priority < n->priority) {
        NodePair splitted = split(root, n->key);
        n->setLeft(splitted.first);
        n->setRight(splitted.second);
        return n;
    }
    // BST(Binary search tree) condition: left < parent < right
    else if (n->key < root->key) {
        root->setLeft(insert(root->left, n));
    }
    else {
        root->setRight(insert(root->right, n));
    }
    return root;
}

node *merge(node *a, node *b) {
    if (a == NULL) return b;
    if (b == NULL) return a;
    if (a->priority < b->priority) {
        b->setLeft(merge(a, b->left));
        return b;
    }
    a->setRight(merge(a->right, b));
    return a;
}

node *erase(node *root, KeyType k) {
    if (root == NULL) return NULL;

    if (root->key == k) {
        node *n = merge(root->left, root->right);
        delete root;
        return n;
    }
    else if (k < root->key) {
        root->setLeft(erase(root->left, k));
    }
    else {
        root->setRight(erase(root->right, k));
    }
    return root;
}

node *nth(node *root, int n) {
    int leftSize = 0;
    if (root->left != NULL) leftSize = root->left->size;
    if (n == (leftSize+1)) return root;
    if (n <= leftSize) return nth(root->left, n);
    return nth(root->right, n - leftSize - 1);
}

int countLT(node *root, KeyType k) {
    if (root == NULL) return 0;
    if (k <= root->key) {
        return countLT(root->left, k);
    }

    int ls = 0;
    if (root->left) ls = root->left->size;

    return ls + 1 + countLT(root->right, k);
}

void deleteAll(node *root)
{
    if (root == NULL) return;

    if (root->left)
        deleteAll(root->left);
    if (root->right)
        deleteAll(root->right);
    delete root;
}

int CASE, N;
int inputs[100];

int main()
{
    freopen("trip.txt", "r", stdin);
    scanf("%d", &CASE);
    for (int t = 1; t <= CASE; ++t) {
        node *root = NULL;

        scanf("%d", &N);
        for (int i = 0; i < N; ++i) {
            scanf("%d", &inputs[i]);

            node *n = new node(inputs[i]);
            root = insert(root, n);
        }

        printf("n-th: [%d] -> %d\n", 2, countLT(root, 2) );
        printf("n-th: [%d] -> %d\n", 2, countLT(root, 1) );

        deleteAll(root);
    }
}
