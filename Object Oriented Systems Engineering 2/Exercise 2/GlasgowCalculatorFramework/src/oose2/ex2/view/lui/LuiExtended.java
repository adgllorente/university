package oose2.ex2.view.lui;

import oose2.ex2.model.CalculatorException;
import oose2.ex2.model.ExtendedCalculator;
/**
 * 
 * Line view for Extended calculator - shows how to extend LuiBasic
 *  
 * @author J Sventek
 * @author tws
 * @version 1.0
 */

/*
 * Tasks for extending LuiBasic
 * 1. provide constructor, deferring to super()
 * 2. override displayError to print LuiExtended instead of LuiBasic
 * 3. override attemptCommand()
 */

public class LuiExtended extends LuiBasic {
	
	/** Gives access to the extended calculator's full interface */
	private ExtendedCalculator exCalc;

	public LuiExtended(ExtendedCalculator theCalc) {
		super(theCalc);
		this.exCalc = theCalc;
		
	}
	
	/**
	 * Overrides displayError so that lines printed indicate that it comes from LuiExtended
	 */
	public void displayError(String err) {
		System.err.println("LuiExtended/" + err);
	}
	
	/**
	 * Override attemptCommand to process Extended-specific commands
	 * Defer to super.attemptCommand() for unrecognized commands
	 */
	public void attemptCommand(String buf) throws CalculatorException {
		try {
			if (buf.equalsIgnoreCase("BodyTemp"))  exCalc.enter("98.6");
			else if (buf.equalsIgnoreCase("swap")) exCalc.swap();
			else if (buf.equalsIgnoreCase("fahr")) exCalc.fahr();
			else if (buf.equalsIgnoreCase("celc")) exCalc.celc();
			else super.attemptCommand(buf);
		} catch (CalculatorException ex) {
			throw ex;
		}
	}
}