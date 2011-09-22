package oose2.ex2;

import oose2.ex2.view.CalcUI;
import oose2.ex2.view.CalculatorFactory;

/**
 * Glasgow Calculator Framework - main entry point.
 * 
 * Invocation requires two arguments:
 *  args[0] indicates the view-type
 *  args[1] indicates the model-type                             
 * 
 * @author J Sventek
 * @author tws
 * @version 1.0
 * 
 * Edit history:
 * 08/03/2008 - initial release
 */
public class Main {
	
	/**
	 * main program for a calculator in the Glasgow Calculator Framework
	 * must be invoked as "java Calculator view-type model-type"
	 * 
	 * @param args args[0] is the view-type, args[1] is the model-type
	 */
	public static void main(String[] args) {
		CalcUI theView = null;
		
		if (args.length != 2) {
			System.err.println("usage: java Calculator view-type model-type");
			System.exit(0);
		}
		try {
			theView = CalculatorFactory.create(args[0], args[1]);
		} catch (Exception ex) {
			System.err.println("Error manufacturing calculator with view="
                               + args[0] + " and model ="+ args[1]);
			System.err.println(ex);
			System.exit(0);
		}
		theView.start();
	}
}
