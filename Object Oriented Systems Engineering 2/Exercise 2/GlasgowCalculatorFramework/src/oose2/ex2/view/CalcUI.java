package oose2.ex2.view;
/**
 * 
 * Interface to be implemented by calculator framework view classes.
 * 
 * @author J Sventek
 * @author tws
 * Version 1.0
 * 
 * Edit history:
 * 08/03/2008 - initial release
 */
public interface CalcUI {
	
	/**
	 * Display the Error string in a view-specific manner
	 * @param err Error string to be displayed
	 */
	void displayError(String err);
	
	/**
	 * Start the calculator
	 */
	void start();

	/**
	 * Initialises this view the specified model.
	 */
	void initialiseUI();
}