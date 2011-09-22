package oose2.ex2.model;
/**
 * Class in the Calculator Framework that provides accumulators
 * 
 * @author J Sventek
 * @author tws
 * @version 1.0
 * 
 * Edit history:
 * 11/02/2009 - initial release
 */
public class Accumulator {

    private Integer count;
    private Double mean;
    private Double variance;

    public Accumulator() {
        this.clear();
    }

    /**
     * clears the member variables associated with this accumulator
     */
    public void clear() {
        count = 0;
        mean = 0.0;
        variance = 0.0;
    }
 
    /**
     * adds value x to the accumulator
     * 
     * we actually maintain the running value of the mean and the variance
     * of the set of values "added" to the accumulator, along with the number
     * of values added.  this algorithm is due to Knuth
     * 
     * while not strictly correct, we set the variance to 0.0 if count == 0 or 1
     * 
     * @param x value to be added to the accumulator
     */
    public void add(Double x) {
        double M2 = variance * ((count > 0) ? (count - 1) : 0.0);
        count++;
        double delta = x - mean;
        mean += delta / count;
        M2 += delta * (x - mean);
        variance = ((count > 1) ? (M2 / (count - 1)) : 0.0);
    }

    /**
     * returns the number of elements that have been added to the accumulator
     * 
     * @return number of elements that have been added to the accumulator
     */
    public int getCount() {
        return count;
    }

    /**
     * return the sum of elements added to the accumulator
     * 
     * @return the sum of elements added to the accumulator
     */
    public Double getTotal() {
        return (mean * count);
    }

    /**
     * returns the mean value of elements added to the accumulator
     * 
     * @return the mean value of elements added to the accumulator
     */
    public Double getMean() {
        return mean;
    }

    /**
     * returns the variance of the elements added to the accumulator
     * returns a variance of 0 if 0 or 1 elements have been added
     * 
     * @return the variance of the elements added to the accumulator
     */
    public Double getVariance() {
        return variance;
    }

    /**
     * returns the standard deviation of the elements added to the accumulator
     * returns a standard deviation of 0 if 0 or 1 elements have been added
     * 
     * @return the standard deviation of the elements added to the accumulator
     */
    public double getStdDev() {
        return Math.sqrt(variance);
    }
}
