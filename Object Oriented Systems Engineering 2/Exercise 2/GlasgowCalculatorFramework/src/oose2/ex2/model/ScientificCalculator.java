package oose2.ex2.model;

/**
 * Class that offer the operations for Scientific Calculator
 * @author 0904327g
 * @version 1.0
 */
public class ScientificCalculator extends BasicCalculator {

	/**
	 * Constructor for the class, it only uses constructor from superclass
	 */
	public ScientificCalculator() {
		super();
	}

	/**
	 * Makes the operation ln(Sy)
	 * @throws CalculatorException
	 */
	public void ln() throws CalculatorException {
		Double a;
		try {
			a = theStack.pop();
		} catch (Exception e) {
			throw new CalculatorException("ln","empty stack");
		}
		theStack.push(new Double(Math.log(a)));
	}

	/**
	 * Makes the operation e^Sy
	 * @throws CalculatorException
	 */
	public void exp() throws CalculatorException {
		Double a;
		try {
			a = theStack.pop();
		} catch (Exception e) {
			throw new CalculatorException("exp","empty stack");
		}
		theStack.push(new Double(Math.exp(a)));
	}

	/**
	 * Makes the operation Sy^Sx
	 * @throws CalculatorException
	 */
	public void pow() throws CalculatorException {
		Double a,b;
		try {
			a = theStack.pop();
			b = theStack.pop();
		} catch (Exception e) {
			throw new CalculatorException("pow","empty stack");
		}
		theStack.push(new Double(Math.pow(a, b)));
	}

	/**
	 * Makes the operation pi*Sy/180
	 * @throws CalculatorException
	 */
	public void rad() throws CalculatorException {
		Double a;
		try {
			a = theStack.pop();
		} catch (Exception e) {
			throw new CalculatorException("rad","empty stack");
		}
		theStack.push(new Double(Math.PI*a/180));
	}
	
	/**
	 * Makes the operation sin(Sy)
	 * @throws CalculatorException
	 */
	public void sin() throws CalculatorException {
		Double a;
		try {
			a = theStack.pop();
		} catch (Exception e) {
			throw new CalculatorException("sin","empty stack");
		}
		theStack.push(new Double(Math.sin(a)));
	}

	/**
	 * Makes the operation cos(Sy)
	 * @throws CalculatorException
	 */
	public void cos() throws CalculatorException {
		Double a;
		try {
			a = theStack.pop();
		} catch (Exception e) {
			throw new CalculatorException("cos","empty stack");
		}
		theStack.push(new Double(Math.cos(a)));
	}
	
	/**
	 * Makes the operation tan(Sy)
	 * @throws CalculatorException
	 */
	public void tan() throws CalculatorException {
		Double a;
		try {
			a = theStack.pop();
		} catch (Exception e) {
			throw new CalculatorException("tan","empty stack");
		}
		theStack.push(new Double(Math.tan(a)));
	}
}
