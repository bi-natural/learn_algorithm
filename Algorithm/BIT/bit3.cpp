/*
 * https://www.topcoder.com/community/data-science/data-science-tutorials/binary-indexed-trees/#2d
 *
 *
 *
 Notation
  BIT – Binary Indexed Tree
  MaxVal – maximum value which will have non-zero frequency
  f[i] – frequency of value with index i, i = 1 .. MaxVal
  c[i] – cumulative frequency for index i (f[1] + f[2] + … + f[i])
  tree[i] – sum of frequencies stored in BIT with index i (latter will be described what index means); sometimes we will write tree frequency instead sum of frequencies stored in BIT
  num¯ – complement of integer num (integer where each binary digit is inverted: 0 -> 1; 1 -> 0 )
NOTE: Often we put f[0] = 0, c[0] = 0, tree[0] = 0, so sometimes I will just ignore index 0.
 */

const int MAX_FREQ = 10000;

int tree[MAX_FREQ+1];

 /* Time complexity: O(log MaxVal).
    Code length: Up to ten lines.
 */
 int read(int idx){
     int sum = 0;
     while (idx > 0){
         sum += tree[idx];
         idx -= (idx & -idx);
     }
     return sum;
 }

/* Time complexity: O(log MaxVal).
   Code length: Up to ten lines.
*/

 void update(int idx ,int val){
    while (idx <= MaxVal){
        tree[idx] += val;
        idx += (idx & -idx);
    }
}

/* For almost every even number idx, it will work in c * O(log idx), where c is strictly less than 1 */

int readSingle(int idx){
    int sum = tree[idx]; // sum will be decreased
    if (idx > 0){ // special case
        int z = idx - (idx & -idx); // make z first
        idx--; // idx is no important any more, so instead y, you can use idx
        while (idx != z){ // at some iteration idx (y) will become z
            sum -= tree[idx];
            // substruct tree frequency which is between y and "the same path"
            idx -= (idx & -idx);
        }
    }
    return sum;
}


void scale1(int c){
    for (int i = 1 ; i <= MaxVal ; i++)
        update(-(c - 1) * readSingle(i) / c , i);
}


void scale2(int c){
    for (int i = 1 ; i <= MaxVal ; i++)
        tree[i] = tree[i] / c;
}

// if in tree exists more than one index with a same
// cumulative frequency, this procedure will return
// some of them (we do not know which one)

// bitMask - initialy, it is the greatest bit of MaxVal
// bitMask store interval which should be searched
int find(int cumFre){
    int idx = 0; // this var is result of function

    while ((bitMask != 0) && (idx < MaxVal)){ // nobody likes overflow :)
        int tIdx = idx + bitMask; // we make midpoint of interval
        if (cumFre == tree[tIdx]) // if it is equal, we just return idx
            return tIdx;
        else if (cumFre > tree[tIdx]){
                // if tree frequency "can fit" into cumFre,
                // then include it
            idx = tIdx; // update index
            cumFre -= tree[tIdx]; // set frequency for next loop
        }
        bitMask >>= 1; // half current interval
    }
    if (cumFre != 0) // maybe given cumulative frequency doesn't exist
        return -1;
    else
        return idx;
}


/* Time complexity: O(log MaxVal).
  Code length: Up to twenty lines.
 */
 
// if in tree exists more than one index with a same
// cumulative frequency, this procedure will return
// the greatest one
int findG(int cumFre){
    int idx = 0;

    while ((bitMask != 0) && (idx < MaxVal)){
        int tIdx = idx + bitMask;
        if (cumFre >= tree[tIdx]){
                // if current cumulative frequency is equal to cumFre,
                // we are still looking for higher index (if exists)
            idx = tIdx;
            cumFre -= tree[tIdx];
        }
        bitMask >>= 1;
    }
    if (cumFre != 0)
        return -1;
    else
        return idx;
}
