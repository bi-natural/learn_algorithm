/*
 * https://community.topcoder.com/stat?c=problem_statement&pm=6551&rd=9990
 
Problem Statement

In meteorology, a common statistical tool is the median of a given set of measurements. (You can find a definition of the median in the Notes section.)

You are writing software for a device that measures temperature once a second. The device has a small digital display. At any moment, the display has to show the median of temperatures measured in the last K seconds.

Before you upload your software into the device, you would like to test it on a computer.

Instead of measuring temperatures, we will use a random number generator (RNG) to generate fake temperatures. Given three ints seed, mul and add, we define a sequence of temperatures:

t0 = seed
tk+1 = (tk * mul + add) mod 65536
In addition to the parameters of the RNG, you will be given two ints N and K.

Consider the sequence containing the first N temperatures generated by the RNG (i.e., values t0 to tN-1). This sequence has N-K+1 contiguous subsequences of length K. For each such subsequence compute its median.

Your method will be given the numbers seed, mul, add, N, and K. Compute all the medians as described above, and return a long containing their sum.


Definition

Class:	FloatingMedian
Method:	sumOfMedians
Parameters:	int, int, int, int, int
Returns:	long
Method signature:	long sumOfMedians(int seed, int mul, int add, int N, int K)
(be sure your method is public)


Notes
-	Given K numbers, their median is the ((K+1)/2)-th smallest of them, rounding down for even K, and indexing from 1.

For example, the median of (1, 2, 6, 5, 4, 3) is 3, and the median of (11, 13, 12, 14, 15) is 13.

Constraints
-	seed, mul, and add are between 0 and 65535, inclusive.
-	N is between 1 and 250,000, inclusive.
-	K is between 1 and 5,000, inclusive.
-	N is greater than or equal to K.

Examples
0)

3
1
1
10
3
Returns: 60
The generated temperatures are: 3, 4, 5, 6, 7, 8, 9, 10, 11, and 12.

The length-3 contiguous subsequences are (3, 4, 5), (4, 5, 6), ..., and (10, 11, 12).

Their medians are 4, 5, ..., 11.

The sum of these medians is 4+5+...+11 = 60.
1)

10
0
13
5
2
Returns: 49
This time the generated temperatures are 10, 13, 13, 13, and 13. The medians you should compute are 10, 13, 13, and 13.
2)

4123
2341
1231
7
3
Returns: 102186
Generated temperatures: 4123, 19382, 23581, 23040, 1743, 18362, 60593.
3)

47
5621
1
125000
1700
Returns: 4040137193
A quite large random test case.
4)

32321
46543
32552
17
17
Returns: 25569
Watch out for integer overflow when generating the temperatures.

*/