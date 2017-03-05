/**
 * @author jaeho
 * 
 */

/**
 * @note
 * 
 * percolation threshold:
 * - T times trials and averaging the results
 * -    95% confidence interval 
 * -    x(t) : fraction of open sites in computational experments
 * -    \mean x : sample mean x (estimation of the percolation theshold)
 *         ->   \sum_{i=1}^{T} x(i) / T
 * -    \stdev s : standard deviation 
 * -       ->   s^2 = ( \sum_{i=1}^{T} (x_i - \mean x)^2 ) / (T - 1)   
 * -    
 * - 1.96 s / root(T)
 * 
 */

public class PercolationStats {
    
    private static final double CONFIDENCE = 1.96;
        
    private int size, T;
    
    private double result[];
    
    private double sampleMean, stdDev;
    
    private int run_experiment()
    {
        Percolation p = new Percolation(size);
        
        while (!p.percolates()) {
            int row = (int) (Math.round(Math.random() * size + 0.5));
            int col = (int) (Math.round(Math.random() * size + 0.5));
            
            if (p.isOpen(row, col))
                continue;
            
            p.open(row, col);
        }
        
        return p.numberOfOpenSites();
    }
    
    public PercolationStats(int n, int trials) 
    {
        if (n <= 0 || trials <= 0) {
            throw new java.lang.IllegalArgumentException();
        }
        
        size = n;
        T = trials;
        
        result = new double[trials];
        
        for (int i = 0; i < T; ++i) {
            result[i] = (double) run_experiment() / (double) (size * size);
        }
        
        sampleMean = 0.0;
        stdDev = 0.0;
        
    }
    public double mean()                          // sample mean of percolation threshold
    {
        for (int i = 0; i < T; ++i) {
            sampleMean += result[i];
        }
          
        sampleMean = sampleMean / T;
        
        return sampleMean;
    }
    
    public double stddev()                        // sample standard deviation of percolation threshold
    {
        double stddev = 0.0;
        
        for (int i = 0; i < T; ++i) {
            double x = result[i] - sampleMean;
            
            stddev += (x * x);
        }
        
        return Math.sqrt(stddev / (T - 1));
    }
    
    public double confidenceLo()                  // low  endpoint of 95% confidence interval
    {
        return ( sampleMean - CONFIDENCE * stdDev / Math.sqrt(T) );
    }
    
    public double confidenceHi()                  // high endpoint of 95% confidence interval
    {
        return ( sampleMean + CONFIDENCE * stdDev / Math.sqrt(T) );
    }
    
    public static void main(String[] args)        // test client (described below)
    {
        if (args.length != 2) 
        {
            throw new java.lang.IllegalArgumentException();
        }
        
        int size = Integer.parseInt(args[0]);
        int times = Integer.parseInt(args[1]);
        
        PercolationStats stats = new PercolationStats(size, times);
        
        System.out.println("mean                    = " + stats.mean());
        System.out.println("stddev                  = " + stats.stddev());
        System.out.println("95% confidence interval = " + stats.confidenceLo() + ", " + stats.confidenceLo());        
    }
}