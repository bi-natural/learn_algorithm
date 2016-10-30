#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

template <typename Test> 
void test (Test t, vector<int>& A)
{
    const clock_t begin = clock();
    t(A);
    const clock_t end = clock();
    cout << (end-begin)/double(CLOCKS_PER_SEC) << " sec\n";
}

void selectionSort(vector<int>& A)
{
    for (size_t i = 0; i < A.size(); ++i) {
        int minIndex = i;
        for (int j = i+1; j < A.size(); ++j) {
            if (A[minIndex] > A[j]) {
                minIndex = j;
            }
        }
        swap(A[i], A[minIndex]);
    }

    cout << "== selectionSort\n";
    for (size_t z = 0; z < A.size(); ++z) {
        cout << A[z] << ", ";
    }
    cout << endl;
}

void insertionSort(vector<int>& A)
{
    for (size_t i = 1; i < A.size(); ++i) {
        for (size_t j = i; j > 0 && A[j - 1] > A[j]; --j) {
            swap(A[j-1], A[j]);
        }
    }

    cout << "== insertionSort\n";
    for (size_t z = 0; z < A.size(); ++z) {
        cout << A[z] << ", ";
    }
    cout << endl;
}

void mergeSort(vector<int>& A)
{
    if (A.size() <= 1) return ; /* sorted */

    vector<int>::size_type mid = A.size() / 2;
    vector<int> Left (A.begin(), A.begin() + mid);
    vector<int> Right (A.begin() + mid, A.end());
    
    mergeSort(Left);
    mergeSort(Right);

    vector<int>::iterator iter1 = Left.begin();
    vector<int>::iterator iter2 = Right.begin();

    A.clear();
    while (iter1 != Left.end() || iter2 != Right.end()) {
        if (iter1 == Left.end()) {
            A.push_back(*iter2++);
        }
        else if (iter2 == Right.end()) {
            A.push_back(*iter1++);
        }
        else if (*iter1 <= *iter2) {
            A.push_back(*iter1++);
        }
        else {
            A.push_back(*iter2++);
        }
    }
}

void t_mergeSort(vector<int>& A) {

    mergeSort(A);

    cout << "== mergeSort\n";
    for (size_t z = 0; z < A.size(); ++z) {
        cout << A[z] << ", ";
    }
    cout << endl;
}

void quickSort(vector<int>& A) {
    if (A.size() <= 1) return;
    if (A.size() == 2) {
        if (A[0] > A[1]) {
            swap(A[0], A[1]);
            return;
        }
    }

    int pivot = A[0];

    vector<int> Left ;
    vector<int> Right ;
    
    for (int i = 1; i < A.size(); i++) {
        if (A[i] < pivot)
            Left.push_back(A[i]);
        else
            Right.push_back(A[i]);
    }

    quickSort(Left);
    quickSort(Right);

    A.clear();
    A.insert(A.begin(), Left.begin(), Left.end());
    A.push_back(pivot);
    A.insert(A.end(), Right.begin(), Right.end());
}

void t_quickSort(vector<int>& A) {

    quickSort(A);

    cout << "== quickSort\n";
    for (size_t z = 0; z < A.size(); ++z) {
        cout << A[z] << ", ";
    }
    cout << endl;
}

int main()
{
    vector<int> v;

    for (int i = 0; i < 100; i++) {
        int n = rand() % 1000 + 1;

        v.push_back(n);
    }

    ios_base::sync_with_stdio(false);

    test(selectionSort, v);
    test(insertionSort, v);
    test(t_mergeSort, v);
    test(t_quickSort, v);
}
