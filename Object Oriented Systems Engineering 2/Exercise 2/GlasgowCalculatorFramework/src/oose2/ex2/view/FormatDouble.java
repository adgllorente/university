package oose2.ex2.view;
/** 
 * Helper class for formatting double precision floating point numbers.
 * 
 * @author J Sventek
 * @author tws
 * @version 1.0
 * 
 * Edit history:
 * 08/03/2008 - initial release
 */
public class FormatDouble {
	
	/** The number of decimal places */
	private int places;

	
	public FormatDouble() {
		places = 2;
	}
	
	/**
	 * Sets the number of places to format double values as strings.
	 * @param n
	 */
	public void setPlaces(int n) {
		places = n;
	}
	
	/**
	 * Formats a Double value according to the number of decimal places set for this
	 * FormatDouble instance.
	 * @param d the value to format.
	 * @return a formatted string representation of the double value.
	 */
	public String format(Double d) {
		String formatString = String.format("%%.%df", places);
		return String.format(formatString, d);
	}
}