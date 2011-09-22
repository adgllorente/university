/*
 * class instances to keep track of occurrences of .XXX
 */
package oose2.ex1b;

public class Country implements Comparable<Country> {
	
	private String theCode;
	private int count;
	
	// CONSTRUCTORS
	/**
	 * create a Country instance from the country code string argument
	 * initialize the count to 1
	 * 
	 * @param	ctry	String for the country code
	 */
	public Country(String ctry) {
		this.theCode = new String(ctry);
		this.count = 1;
	}
	
	/**
	 * create a copy of an existing Country instance
	 * 
	 * @param	cntry	Existing Country instance
	 */
	public Country(Country cntry) {
		this.theCode = new String(cntry.theCode);
		this.count = cntry.count;
	}
	
	// METHODS
	/**
	 * Determine if this.theCode is equal to the supplied ctry.theCode
	 * 
	 * @param	ctry	the supplied country code
	 * @return			true/false if ctry.theCode == this.theCode
	 */
	public boolean equals(Country ctry) {
		return (this.theCode.equals(ctry.theCode));
	}
	
	/**
	 * Increment the count associated with this
	 * 
	 */
	public void increment() {
		this.count++;
	}
	
	/**
	 * Obtain the count associated with this
	 * 
	 * @return	count associated with this
	 */
	public int count() {
		return (this.count);
	}
	
	/**
	 * Obtain the country code associated with this
	 * 
	 * @return	country code associated with this
	 */
	public String countryCode() {
		return (this.theCode);
	}
	
	/**
	 * compares this Country with another
	 * if this.count != ctry.count, returns difference of their counts
	 * else returns this.theCode.compareTo(ctry.theCode)
	 * 
	 * @param	ctry	the other countryto compare against
	 * @return			<0, 0 or >0 depending upon the result of the comparison
	 */
	public int compareTo(Country ctry) {
		int result;
		if ((result = this.count - ctry.count) == 0)
			result = this.theCode.compareTo(ctry.theCode);
		return result;
	}
	
	public String toString() {
		return String.format("%-5s%7d", this.theCode,this.count);
	}
}