package oose2.ex2.model;
/**
 * 
 * Glasgow Calculator Framework (GCF) - specific exception class
 * 
 * @author J Sventek
 * @author tws
 * @version 1.0
 * 
 * Edit history:
 * 08/03/2008 - initial release
 */
public class CalculatorException extends Exception {
	private static final long serialVersionUID = -2203827161787293483L;
	private String function;
	private String reason;
	
	/**
	 * Constructor for GCF-specific exception
	 * @param f name of function generating the exception
	 * @param r the reason for the exception
	 */
	public CalculatorException (String f, String r) {
		function = new String(f);
		reason = new String(r);
	}
	
	/**
	 * Concatenates the function and reason strings
	 */
	public String toString() {
		return function + ": " + reason;
	}
}