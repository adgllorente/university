package oose2.ex2.view;

import oose2.ex2.model.BasicCalculator;
import oose2.ex2.model.ExtendedCalculator;
import oose2.ex2.view.gui.GuiBasic;
import oose2.ex2.view.gui.GuiExtended;
import oose2.ex2.view.lui.LuiBasic;
import oose2.ex2.view.lui.LuiExtended;

/** 
 * Factory class for creating matching model-view pairs.  Consists of a single static method,
 * returning an interface to the view object that was manufactured.
 * 
 * This class must be modified if new models are added to the framework.
 * 
 * @author J Sventek
 * @author tws
 * @version 1.0
 * 
 * Edit history:
 * 08/03/2008 - initial release
 */
public class CalculatorFactory {
	
	public static enum CalculatorView {LINE,GRAPHICAL};
	
	public static enum CalculatorModel {BASIC,EXTENDED}
	
	/**
	 * Constructs matching model-view object pair, returning an interface to the view object.
	 * @param view string representing the type of view desired, "Line" or "Graphical"
	 * @param model string representing the type of model desired either "Basic" or "Extended"
	 * @return interface to the view object created
	 * @throws Exception if either the view-type or model-type are unknown
	 */	
	public static CalcUI create(String view, String model) throws Exception {
		
		//This method is a wrapper for create(CalculatorView, CalculatorModel) that converts
		//string representations of calculator view and model types into their
		//equivalent enumeration members.
		
		CalculatorView eView = null;
		CalculatorModel eModel = null;
		
		if (view.equalsIgnoreCase("Line")) eView = CalculatorView.LINE;
		else if (view.equalsIgnoreCase("Graphical")) eView = CalculatorView.GRAPHICAL;
		else throw new Exception("Unknown View");
		
		if (model.equalsIgnoreCase("Basic")) eModel = CalculatorModel.BASIC;
		else if (model.equalsIgnoreCase("Extended")) eModel = CalculatorModel.EXTENDED;
		else throw new Exception("Unknown Model");
			
		return create(eView,eModel);
	}
	
	/**
	 * Constructs matching model-view object pair, returning an interface to the
	 * view object. The method guarantees to return a CalcUI instance for any
	 * combination of non-null enumeration members.
	 * 
	 * @param view
	 *            enumeration member representing the type of view desired
	 * @param model
	 *            enumeration representing the type of model desired
	 * @return interface to the view object created
	 */	
	public static CalcUI create(CalculatorView view, CalculatorModel  model) {
		//
		CalcUI ui = null;
		if (model.equals(CalculatorModel.BASIC)){
			BasicCalculator theModel = new BasicCalculator();	
			
			if (view.equals(CalculatorView.LINE))
				ui = new LuiBasic(theModel);
			else if (view.equals(CalculatorView.GRAPHICAL))
				ui = new GuiBasic(theModel);
			
		} else if (model.equals(CalculatorModel.EXTENDED)){
			ExtendedCalculator theModel = new ExtendedCalculator();	
			
			if (view.equals(CalculatorView.LINE))
				ui = new LuiExtended(theModel);
			else if (view.equals(CalculatorView.GRAPHICAL))
				ui = new GuiExtended(theModel);
		}
		ui.initialiseUI();
		return ui;
	}
}