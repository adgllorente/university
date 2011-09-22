package oose2.ex2.model;
/**
 * 
 * Example extension to the basic calculator
 * 
 * Additional commands supported:
 * 
 * 
 * @author J Sventek
 * @author tws
 * @version 1.0
 * 
 * Edit history:
 * 08/03/2008 - initial release
 */
public class ExtendedCalculator extends BasicCalculator {
	/**
	 * Constructor for Extended Calculator
	 * Since stack for calculator is created in the superclass
	 * simply invoke the superclass constructor
	 */
	public ExtendedCalculator() {
		super();
	}
	
	/**
	 * replace the top element of the stack (a Celcius temperature value) with the equivalent Fahrenheit temperature
	 */
	public void fahr() throws CalculatorException {
		Double a;
		try {
			a = theStack.pop();
		} catch (Exception ex) {
			throw new CalculatorException("fahr", "empty stack");
		}
		theStack.push(1.8 * a + 32.0);
	}
	
	/**
	 * replace the top element of the stack (a Fahrenheit temperature value) with the equivalent Celcius temperature
	 */
	public void celc() throws CalculatorException {
		Double a;
		try {
			a = theStack.pop();
		} catch (Exception ex) {
			throw new CalculatorException("celc", "empty stack");
		}
		theStack.push(new Double(5.0 /9.0 * (a - 32.0)));
	}
	
	/**
	 * swap the top two elements of the stack
	 */
	public void swap() throws CalculatorException {
		Double a, b;
		try {
			b = theStack.pop();
	
			a = theStack.pop();
		} catch (Exception ex) {
			throw new CalculatorException("swap", "empty stack");
		}
		theStack.push(b);
		theStack.push(a);
	}
}