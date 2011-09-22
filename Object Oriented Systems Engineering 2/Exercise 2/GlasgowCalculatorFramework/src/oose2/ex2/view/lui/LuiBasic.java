package oose2.ex2.view.lui;
/** 
 * Line view for basic calculator
 *  
 * @author J Sventek
 * @author tws
 * @version 1.0
 * 
 * Edit history:
 * 08/03/2008 - initial release
 */

import java.util.Scanner;

import oose2.ex2.model.BasicCalculator;
import oose2.ex2.model.CalculatorException;
import oose2.ex2.view.CalcUI;
import oose2.ex2.view.FormatDouble;

public class LuiBasic implements CalcUI{
	
	protected BasicCalculator theCalc;
	protected FormatDouble fmt;
	
	private Scanner stdin;
	
	/**
	 * Creates scanner to System.in for line-oriented interface
	 */
	public LuiBasic(BasicCalculator theCalc) {
		this.theCalc = theCalc;
		fmt = new FormatDouble();
	}
	
	/**
	 * Initializes the line-oriented interface
	 */
	@Override
	public void initialiseUI() {
		this.stdin = new Scanner(System.in);
	}
	
	/**
	 * Display the error on System.err
	 */
	public void displayError(String err) {
		System.err.println("LuiBasic/" + err);
	}
	
	/**
	 * start the ui interface - while not EOF, fetches next white-space-separated token and processes
	 */
	public void start() {
		String buf = null;
		
		while (true) {
			try {
				String top = fmt.format(theCalc.top());
				System.out.println(top);
				System.out.flush();
			} catch (CalculatorException ex) {
				System.out.println("(empty stack)");
			}
			if (! stdin.hasNext()) break;
			buf = stdin.next();
			try {
				attemptCommand(buf);
			} catch (CalculatorException ex) {
				displayError(ex.toString());
			}
		}
	}
	
	/**
	 * attempts to convert 'buf' to a double; if successful, pushes it onto the stack
	 * otherwise, compares 'buf' against known commands, and executes if found
	 * throws exception if unknown command
	 * @param buf token containing a double or a command
	 * @throws CalculatorException if unknown command or exception while processing
	 */
	public void attemptCommand(String buf) throws CalculatorException {		
		try {
			if (isNumber(buf))			theCalc.enter(buf);
			
			//Binary operation
			else if (buf.equals("+"))	theCalc.plus();
			else if (buf.equals("-"))	theCalc.minus();
			else if (buf.equals("*"))	theCalc.times();
			else if (buf.equals("/"))	theCalc.divide();
			
			//Unary operations
			else if (buf.equalsIgnoreCase("Clear"))		theCalc.clear();
			else if (buf.equalsIgnoreCase("Sign"))  	theCalc.sign();
			else if (buf.equalsIgnoreCase("Invert"))	theCalc.invert();
			else if (buf.equalsIgnoreCase("Square"))    theCalc.square();
			else if (buf.equalsIgnoreCase("Sqrt"))		theCalc.sqrt();
			
			//Accumulator operations
			else if (buf.equalsIgnoreCase("Aclear"))	theCalc.Aclear();
			else if (buf.equalsIgnoreCase("Arecall"))	theCalc.Arecall();
			else if (buf.equalsIgnoreCase("Aplus"))		theCalc.Aplus();
			else if (buf.equalsIgnoreCase("Astore"))	theCalc.Astore();
			else if (buf.equalsIgnoreCase("Pi"))		theCalc.enter(Math.PI);
			else if (buf.equalsIgnoreCase("Fix")) {
				int n = (int)(theCalc.pop() + 0.00001);
				fmt.setPlaces(n);
			} else System.err.println("Unknown command - " + buf);
		} catch (CalculatorException ex) {
			throw ex;
		}
	}

	private boolean isNumber(String buf) {
		try {
			Double.valueOf(buf);
			return true;
		} catch (Exception ex){
			return false;
		}
	}
}
