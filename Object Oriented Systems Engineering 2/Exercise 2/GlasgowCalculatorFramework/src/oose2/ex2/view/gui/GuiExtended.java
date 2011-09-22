package oose2.ex2.view.gui;
/**
 * Graphical view for Extended calculator - shows how to extend GuiBasic
 *  
 * @author J Sventek
 * @author tws
 * @version 1.0
 * 
 * Edit history:
 * 08/03/2008 - initial release
 */

import java.awt.GridLayout;
import java.awt.Color;

import javax.swing.JPanel;

import oose2.ex2.model.ExtendedCalculator;

public class GuiExtended extends GuiBasic {
	private static final long serialVersionUID = -5368279260811158496L;
	
	/** The calculator instance for this view, accessible via the ExtendedCalculator features.*/
	private ExtendedCalculator exCalc;
	
	/**
	 * Constructs a new extended graphical view for the specified calculator model.
	 * @param theCalc the model for the view to present.
	 */ 
	public GuiExtended(ExtendedCalculator theCalc) {
		//Pass the calculator to the super class (via the restricted BasicCalculator interface)
		super(theCalc);
		//Retain the extended calculator instance to access extended features.
		this.exCalc = theCalc;
	}
	
	/**
	 * Overrides super.initialiseUI() to provide extended features.
	 */
	public void initialiseUI() {
		// Create panel container for extra buttons
		JPanel jplExtra = new JPanel();			
		
		//  set layout manager for extra buttons
		jplExtra.setLayout(new GridLayout(1, 4, 2, 2));
	
		// Add extra buttons - BTemp, fahr, celc, x<>y
		jplExtra.add(new CalculatorButton("BTemp", Color.green));
		jplExtra.add(new CalculatorButton("Fahr", Color.red));
		jplExtra.add(new CalculatorButton("Celc", Color.red));
		jplExtra.add(new CalculatorButton("x<>y", Color.red));
		//provide that JPanel object to the super class
		super.setExtra(jplExtra);
		
		// init the super class UI components
		super.initialiseUI();
		
	}

	/**
	 * overrides processOperation() in super class to handle Extended-specific operations.
	 * if not an Extended-specific operation, defer to super.processOperation to handle
	 * @param cmd command string for calculator operation
	 */
	public void processOperation(String cmd) {
		try {
			if (cmd.equalsIgnoreCase("Fahr")) exCalc.fahr();
			else if (cmd.equalsIgnoreCase("Celc"))exCalc.celc();
			else if (cmd.equalsIgnoreCase("x<>y"))exCalc.swap();
			else if (cmd.equalsIgnoreCase("BTemp"))theCalc.enter("98.6");
			else super.processOperation(cmd);
			
			displayTop();
		
		} catch (Exception ex) {
			displayError(ex.toString());
		}
		
	}
}
