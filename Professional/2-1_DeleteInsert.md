## 증명의 중요성

- Binary Search Tree 변형
- Hanoi Tower 변형
- 물통
- Proximity Problem
- 천정화
- 뜬금없는 Greedy
- Dynamic All-Pair Shortest Path

### 인접한 값을 delete 하면서 insert

문제: Binary Search Tree 에서 보통의 delete 외에 **insert and delete next smallest**.

- Binary Search Tree 특징
  - binary = 노드의 child가 2개
  - <node>의 왼쪽 sub-tree에는 <node>값보다 모두 작고, 오른쪽 sub-tree는 <node>값보도 모두 크다.
  - O(log n)에 검색(search) 가능
  - O(log n)에 삽입(insert) 가능
  - 기타
    - 순서대로 출력하기
    - Tree의 height 구하기
    - 두 BST의 merge 하기
    - X 보다 작은 원소의 수 찾기
    - k번째 원소 찾기


- BST 자료 구조
  - 값
  - parent, left (sub-tree), right (sub-tree)

```
  struct BST {
      int value;
      BST *parent;
      BST *left, *right;

      BST(BST *P, int v) : value(v), parent(P), left(NULL), right(NULL) { }
  }
```
- BST에서 search 알고리즘 : 목표값 (x)
  - 현재 node가 NULL (없음)이면 찾는데 실패함
  - 그렇지 않은데,
    - 값이 현재 node 와 같으면 찾았음 !
    - 값이 현재 node 와 같지 않은데
      - 값이 현재 node 보다 작으면 왼쪽 sub-tree에서 x를 찾고
      - 값이 현재 node 보다 크면 오른쪽 sub-tree에서 x를 찾는다.
```
  BST* search(BST *T, x)
  {
    if (T == NULL) return NULL;
    if (T->value > x) return search(T->left, x);
    else if (T->value < x) return search(T->right, x);
    else return T;
  }
```

- BST에서 insert 알고리즘 : 신규값 (x)
  - search하다가 실패! 하는 곳에 넣는다.

```
  BST* insert(BST *T, x)
  {
    if (T == NULL) return NULL;

    if (T->value > x) {
      if (T->left)
        return insert(T->left, x);
      else
        return T->left = new BST(T, x);
    }
    else if (T->value < x) {
      if (T->right)
        return insert(T->right, x);
      else
        return T->right = new BST(T, x);
    }
    else
      return T;               /* 이미 있음 ; 값이 같음 */
  }
```

- BST에서 delete 알고리즘 : 기존값 (x)
  - search하여 해당 노드를 삭제한다.
  - 삭제노드가 leaf 노드이면 바로 삭제하고 종료
  - 삭제노드가 left, right 둘중 하나만 있으면 해당 sub-tree를 parent에 붙인다.
  - 삭제노드가 left, right 모두 갖고 있으면 right sub-tree의 가장 작은 값을 찾아 해당 값을 복사하고 찾은 노드(반드시 leaf 노드)를 삭제한다.

```
  <TO-BE>
```

- BST에서 '특정값(A)값보다 작은 값중 최소값(X)을 삭제하고 A를 삽입한다.'
  - BST에서 A를 search한다.
  - Search가 실패하는 순간 A에서 X를 찾아가는 알고리즘을 수행하여 X를 찾는다.
    - 해당 노드에서 parent를 찾아올라가는데, left sub-tree다가 최초로 right sub-tree이 노드를 만났을 때가 X 임.
  - X 대신 A를 기록한다.
