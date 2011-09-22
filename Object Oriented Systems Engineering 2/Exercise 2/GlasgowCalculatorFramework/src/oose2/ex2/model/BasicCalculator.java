package oose2.ex2.model;
/**
 * A Basic Reverse Polish Notation Calculator
 * 
 * <p>Assume the top of the stack is y, and the next element is x. The following binary operations are supported:</a>
 * 
 * <ul>
 *   <li>plus   replace x and y by x+y </li>
 *   <li>minus  replace x and y by x-y </li>
 *   <li>times  replace x and y by x*y </li>
 *   <li>divide replace x and y by x/y </li>
 *   <li>Aplus  add x to Accumulator<y>, leaving x on top of stack </li>
 *   <li>Astore set Accumulator<y> to x, leaving x on top of stack </li>
 * </ul>
 * 
 * <p>The following unary operations are supported:</p>
 * 
 * <ul>
 * <li>sign    replaces y by -y </li>
 * <li>invert  replaces y by 1/y </li>
 * <li>square  replaces y by y*y </li>
 * <li>sqrt    replaces y by sqrt(y) </li>
 * <li>Aclear  clear Accumulator[y]; replace y by value of Accumulator[y]  </li>
 * <li>Arecall replace y by Accumulator[y] </li>
 * </ul>
 * 
 * @author J Sventek
 * @author tws
 * @version 1.1
 * 
 * Edit history:
 * 08/03/2008 - initial release
 * 10/02/2009 - addition of accumulators
 */
import java.util.Stack;
import java.util.ArrayList;

public class BasicCalculator {
	
	/*
	 * The following instance variables are protected so that extended calculator
	 * classes can access them directly
	 */
	
	/** A constant close to zero used for testing results of divisions */
	protected static final double SMALL_DOUBLE = 1.0e-300;
	
	/** The current calculation state */
	protected Stack<Double> theStack = null;
	
	/** The current storage state */
	private ArrayList<Accumulator> theAccumulators = null;
	
	/**
	 * create an empty Reverse Polish Notation calculator - creates an empty stack of Doubles
	 * and array of 10 accumulators
	 */
	public BasicCalculator() {
		this.clear();
	}
	
	/**
	 * clear the calculator by purging all elements from the stack and reseting all values of accumulators
	 */
	public void clear() {
		theStack = new Stack<Double>();
		theAccumulators = new ArrayList<Accumulator>(10);
		for (int i = 0; i < 10; i++) {
			theAccumulators.add(new Accumulator());
		}
	}
	
	//arithmetic operations.
	
	/**
	 * replace the top two elements of the stack by their sum
	 */
	public void plus() throws CalculatorException {
		Double a, b;
		try {
			b = theStack.pop();
			a = theStack.pop();
		} catch (Exception ex) {
			throw new CalculatorException("plus", "empty stack");
		}
		theStack.push(a+b);
	}
	
	/**
	 * replace the top two elements of the stack by their difference
	 */
	public void minus() throws CalculatorException {
		Double a, b;
		try {
			b = theStack.pop();
			a = theStack.pop();
		} catch (Exception ex) {
			throw new CalculatorException("minus", "empty stack");
		}
		theStack.push(a-b);
	}
	
	/**
	 * replace the top two elements of the stack by their product
	 */
	public void times() throws CalculatorException {
		Double a, b;
		try {
			b = theStack.pop();
			a = theStack.pop();
		} catch (Exception ex) {
			throw new CalculatorException("times", "empty stack");
		}
		theStack.push(a*b);
	}
	
	/**
	 * replace the top two elements of the stack by their quotient
	 */
	public void divide() throws CalculatorException {
		Double a, b;
		try {
			b = theStack.pop();
			a = theStack.pop();
		} catch (Exception ex) {
			throw new CalculatorException("divide", "empty stack");
		}
		if (Math.abs(b) < SMALL_DOUBLE)
			throw new CalculatorException("divide", "divide by zero");
		theStack.push(a/b);
	}
	
	/**
	 * replace top element by -(top element)
	 */
	public void sign() throws CalculatorException {
		Double a;
		try {
			a = theStack.pop();
		} catch (Exception ex) {
			throw new CalculatorException("sign", "empty stack");
		}
		theStack.push(-a);
	}
	
	/**
	 * replace top element by 1/(top element)
	 */
	public void invert() throws CalculatorException {
		Double a;
		try {
			a = theStack.pop();
		} catch (Exception ex) {
			throw new CalculatorException("invert", "empty stack");
		}
		if (Math.abs(a) < SMALL_DOUBLE)
			throw new CalculatorException("invert", "divide by zero");
		theStack.push(1/a);
	}
	
	/**
	 * replace the top element of the stack by its square
	 */
	public void square() throws CalculatorException {
		Double a;
		try {
			a = theStack.pop();
		} catch (Exception ex) {
			throw new CalculatorException("square", "empty stack");
		}
		theStack.push(a*a);
	}
	
	/**
	 * replace the top element of the stack by its positive square root
	 */
	public void sqrt() throws CalculatorException {
		Double a;
		try {
			a = theStack.pop();
		} catch (Exception ex) {
			throw new CalculatorException("sqrt", "empty stack");
		}
		if (a < 0.0)
			throw new CalculatorException("sqrt", "negative number");
		theStack.push(Math.sqrt(a));
	}
	
	/**
	 * return the top element of the stack without removing it
	 * 
	 * @return	the top element on the stack
	 */
	public Double top() throws CalculatorException {
		Double a;
		try {
			a = theStack.peek();
		} catch (Exception ex) {
			throw new CalculatorException("top", "empty stack");
		}
		return a;
	}
	
	//stack operations
	
	/**
	 * pop the top element of the stack and return it
	 * 
	 * @return	the top element on the stack
	 */
	public Double pop() throws CalculatorException {
		Double a;
		try {
			a = theStack.pop();
		} catch (Exception ex) {
			throw new CalculatorException("pop", "empty stack");
		}
		return a;
	}
	
	/**
	 * push the number represented by 's' onto the stack
	 * 
	 * @param s	string representation of a floating point number
	 */
	public void enter(String s) {
		Double d = new Double(s);
		enter(d);
	}
	
	/**
	 * push the double represented by 'd' onto the stack
	 * 
	 * @param d double precision floating point number
	 */
	public void enter(Double d) {
		theStack.push(d);
	}

	//Accumulator operations.
	
	/**
	 * replace index on stack by value of accumulator with that index AFTER
	 * THE ACCUMULATOR HAS BEEN CLEARED (0.0)
	 */
	public void Aclear() throws CalculatorException {
		Accumulator accumulator = retrieveAccumulator();
		accumulator.clear();	
		theStack.push(accumulator.getTotal());
	}
	
	/**
	 * replace index on stack by value of accumulator with that index
	 */
	public void Arecall() throws CalculatorException {
		Accumulator accumulator = retrieveAccumulator();
		theStack.push(accumulator.getTotal());		
	}

	/**
	 * add x to accumulator indexed by y, leaving x on top of stack
	 */
	public void Aplus() throws CalculatorException {
		Accumulator accumulator = retrieveAccumulator();
		Double a;
		try {
			a = theStack.peek();
		} catch (Exception ex) {
			throw new CalculatorException("Aplus", "empty stack");
		}
		accumulator.add(a);
	}

	/**
	 * replace value of accumulator indexed by y with x, leave x on top of stack
	 */
	public void Astore() throws CalculatorException {
		Accumulator accumulator = retrieveAccumulator();
		Double a;
		try {
			a = theStack.peek();
		} catch (Exception ex) {
			throw new CalculatorException("Astore", "empty stack");
		}
		accumulator.clear();
		accumulator.add(a);
	}
	
	/**
	 * Protected method for accessing accumulators
	 * @return
	 * @throws CalculatorException
	 */
	protected Accumulator retrieveAccumulator() throws CalculatorException{
		Accumulator acc = null;
		Double b;
		try{
			b = theStack.pop();
		} catch (Exception e){
			throw new CalculatorException("Accumulator recall", "empty stack");
		}
		int index = (int) (b + 0.1);
		if (index < 0 || index > 9) 
			throw new CalculatorException("Accumulator recall", "invalid accumulator index");
		acc = theAccumulators.get(index);
		
		return acc;
	}
}
