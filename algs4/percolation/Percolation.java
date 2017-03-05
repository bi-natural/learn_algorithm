/**
 * @author jaeho
 * 
 */

/**
 * @note
 * 
 * goal: estimate the value of the *percolation theshold* via *Monte Carlo Simulation*
 * 
 * intro
 * - percolation: *poruos landscape condition with water*, water will be able to drain through to the bottom.
 * 
 * given condition
 * - n x n grid sites
 * - each site -> open/blocked state
 * - full open state : it has opened path from top to bottom.
 * 
 * problem
 * - the sites are independently set to be open with probability $p$ (otherwise blocked $1-p$)
 * - p \approx 0, the sites does not percloate.
 * - p \approx 1, the sites maybe percolate.
 * - coner case: by convention, the row and column indices are integer between 1..n (1,1) -> UL (upper-left)
 * - the constructor should throw a java.lang.illegalArgumentException (n \le 0)
 * 
 * class WeightedQuickUnionUF
 * - 
 */

import edu.princeton.cs.algs4.WeightedQuickUnionUF;

public class Percolation {
   
   private int size;
   private boolean[] sites;
   private int numOfOpenSites;
   
   private int vTopIndex, vBottomIndex;
   
   private WeightedQuickUnionUF unionFind;
   
   private boolean isValidIndex(int row, int col)
   {
       return (row >= 1) && (row <= size) && (col >= 1) && (col <= size);
   }
  
   private int toUnionIndex(int row, int col)
   {
       return (row - 1) * size + (col - 1);
   }
   
   private void union(int idx1, int idx2)
   {
       if (sites[idx1] && sites[idx2])
       {
           unionFind.union(idx1, idx2);
       }
   }
   
   public Percolation(int n)                // create n-by-n grid, with all sites blocked
   {
       if (n <= 0)
           throw new java.lang.IllegalArgumentException();
       
       size = n;
       sites = new boolean[size*size + 2];
       
       for (int i = 0; i < (size*size); ++i) 
       {
           sites[i] = false;
       }
       
       numOfOpenSites = 0;
       
       vTopIndex = size * size;    
       vBottomIndex = vTopIndex + 1;
       sites[vTopIndex] = true;
       sites[vBottomIndex] = true;
       
       unionFind = new WeightedQuickUnionUF(size * size + 2);
   }
   
   private void North(int row, int col, int index) {
       if (row == 1) 
           union(index, vTopIndex);
       else
           union(index, toUnionIndex(row - 1, col));
   }
   
   private void West(int row, int col, int index) {
       if (col != 1)
           union(index, toUnionIndex(row, col - 1));
       
   }
   
   private void East(int row, int col, int index) {
       if (col != size)
           union(index, toUnionIndex(row, col + 1));
   }
   
   private void South(int row, int col, int index) {
       if (row == size) 
           union(index, vBottomIndex);
       else
           union(index, toUnionIndex(row + 1, col));
   }
   
   public    void open(int row, int col)    // open site (row, col) if it is not open already
   {
       if (isOpen(row, col))                // check already open site & IndexOutOfBoundsException check at Here
           return;                          
       
       int index = toUnionIndex(row, col);
       
       sites[index] = true;
       numOfOpenSites++;

       North(row, col, index);
       West(row, col, index);
       East(row, col, index);
       South(row, col, index);
       
   }
   
   public boolean isOpen(int row, int col)  // is site (row, col) open?
   {
       if (!isValidIndex(row, col))
           throw new java.lang.IndexOutOfBoundsException();
       
       return sites[toUnionIndex(row, col)];           
   }
   
   public boolean isFull(int row, int col)  // is site (row, col) full?
   {
       if (!isOpen(row, col))
           return false;
       
       return unionFind.connected(toUnionIndex(row, col), vTopIndex);
   }
   
   public     int numberOfOpenSites()       // number of open sites
   {
       return numOfOpenSites;
   }
   
   public boolean percolates()              // does the system percolate?
   {
       return unionFind.connected(vTopIndex, vBottomIndex);
   }

   public static void main(String[] args)   // test client (optional)
   {
       ;
   }
}
