
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

struct tree_m {
    int value;
    tree_m* parent;
    vector<tree_m*> children;
};

struct tree_b {
    int value;
    tree_b *parent;
    tree_b *left;
    tree_b *right;

    tree_b(int v) : value(v) { parent = left = right = NULL; }

    tree_b* setLeft(int v) {
        printf(" setLeft(%d) -> %d\n", value, v);
        left = new tree_b(v);
        left->parent = this;
        return left;
    }

    tree_b* setRight(int v) {
        printf(" setRight(%d) -> %d\n", value, v);
        right = new tree_b(v);
        right->parent = this;
        return right;
    }

    /*
     * pre-order
     *      <root> ---> <left> ---> <right>
     * in-order
     *      <left> ---> <root> ---> <right>
     * post-order
     *      <left> ---> <right> ---> <root>
     */
};

void traverse_preorder(tree_b *root) {
    if (root != NULL) {
        printf("%d ", root->value);
        if (root->left)
            traverse_preorder(root->left);
        if (root->right)
            traverse_preorder(root->right);
    }
}

void traverse_inorder(tree_b *root) {
    if (root != NULL) {
        if (root->left)
            traverse_inorder(root->left);
        printf("%d ", root->value);
        if (root->right)
            traverse_inorder(root->right);
    }
}

void traverse_postorder(tree_b *root) {
    if (root != NULL) {
        if (root->left)
            traverse_postorder(root->left);
        if (root->right)
            traverse_postorder(root->right);
        printf("%d ", root->value);
    }
}

tree_b *delete_all(tree_b *root) {
    if (root != NULL) {
        if (root->left)
            root->left = delete_all(root->left);
        if (root->right)
            root->right = delete_all(root->right);
        delete root;
    }
    return NULL;
}

void print_postorder(const vector<int>& pre, const vector<int>& in) {
    if (pre.empty())
        return;

    const int& root = pre[0];
    int  left = find(in.begin(), in.end(), root) - in.begin();
    int  right = in.size() - left - 1;

    print_postorder(
        vector<int>(pre.begin()+1, pre.begin()+left+1),
        vector<int>(in.begin(), in.begin()+left)
    );

    print_postorder(
        vector<int>(pre.begin()+left+1, pre.end()),
        vector<int>(in.begin()+left+1, in.end())
    );
    printf("%d ", root);
}

int main()
{
    // build-tree
    freopen("tree1.txt", "r", stdin);
    int n, v;
    scanf("%d", &n);
    scanf("%d", &v);

    tree_b *root = new tree_b(v);
    tree_b *a = root;
    tree_b *b = root;
    for (int i = 1, v; i < n; ++i) {
        scanf("%d", &v);
        if (i%2) {
            a = a->setLeft(v);
        } else {
            b = b->setRight(v);
        }
    }

    printf("pre-order: ");
    traverse_preorder(root);
    printf("\n");

    printf("in-order: ");
    traverse_inorder(root);
    printf("\n");

    printf("post-order: ");
    traverse_postorder(root);
    printf("\n");

    delete_all(root);

    // [21.3] 트리 순회 순서 변경 (ID: TRAVERSAL, 난이도 하)
    freopen("tree2.txt", "r", stdin);
    int Case;
    vector<int> pre_order, in_order;
    scanf("%d", &Case);
    for (int t = 1; t <= Case; ++t) {
        scanf("%d", &n);
        for (int i = 0, d; i < n; ++i) {
            scanf("%d", &d); pre_order.push_back(d);
            printf("%d ", d);
        }
        printf("\n");
        for (int i = 0, d; i < n; ++i) {
            scanf("%d", &d); in_order.push_back(d);
            printf("%d ", d);
        }
        printf("\n");

        print_postorder(pre_order, in_order);
        printf("\n");
    }
}
