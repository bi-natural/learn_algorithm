/*

Insertion Sort

After i iterations the first i elements are ordered.

In each iteration the next element is bubbled through the sorted section until it reaches the right spot:

sorted  | unsorted
1 3 5 8 | 4 6 7 9 2
1 3 4 5 8 | 6 7 9 2
The 4 is bubbled into the sorted section

Pseudocode:

for i in 1 to n
   for j in i downto 2
       if array[j - 1] > array[j]
           swap(array[j - 1], array[j])
       else
           break
Bubble Sort

After i iterations the last i elements are the biggest, and ordered.

In each iteration, sift through the unsorted section to find the maximum.

unsorted  | biggest
3 1 5 4 2 | 6 7 8 9
1 3 4 2 | 5 6 7 8 9
The 5 is bubbled out of the unsorted section

Pseudocode:

for i in 1 to n
   for j in 1 to n - i
        if array[j] > array[j + 1]
            swap(array[j], array[j + 1])
Note that typical implementations terminate early if no swaps are made during one of the iterations of the outer loop (since that means the array is sorted).

Difference

In insertion sort elements are bubbled into the sorted section, while in bubble sort the maximums are bubbled out of the unsorted section.

*/
