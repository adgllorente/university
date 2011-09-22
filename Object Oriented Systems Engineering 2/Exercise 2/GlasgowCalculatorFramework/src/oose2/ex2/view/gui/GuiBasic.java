package oose2.ex2.view.gui;
/**
 * Graphical view for Basic calculator, derived from "A basic Java Swing
 * Calculator" by B. Hemanth, http://www.java-swing-tutorial.com
 * 
 * @author J Sventek
 * @version 1.0
 */

/*
 * Substantially modified and refactored to fit into the calculator framework.
 * The following naming conventions of the original author have been maintained:
 * 	1. All JLabel components start with jlb*
 * 	2. All JPanel components start with jpl*
 * 	3. All JMenu components start with jmenu*
 * 	4. All JMenuItem components start with jmenuItem*
 * 	5. All JDialog components start with jdlg*
 * 	6. All JButton components start with jbn*
 */
import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Font;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyEvent;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;

import javax.swing.JButton;
import javax.swing.JDialog;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;
import javax.swing.JPanel;
import javax.swing.KeyStroke;

import oose2.ex2.model.BasicCalculator;
import oose2.ex2.model.CalculatorException;
import oose2.ex2.view.CalcUI;
import oose2.ex2.view.FormatDouble;

public class GuiBasic extends JFrame implements ActionListener, CalcUI {
	private static final long serialVersionUID = 4716201094687882720L;

	/** Maximum number of characters permitted for input */
	public final int MAX_INPUT_LENGTH = 20;
	
	/** Maintains whether the display should be cleared when a digit button is pressed */
	private boolean clearOnNextDigit;
	
	/** A helper for formatting double values for display */
	protected FormatDouble fmt;
	
	/** The calculator model for this view */
	protected BasicCalculator theCalc;

	/* private GUI components */
	private JMenu jmenuFile, jmenuHelp;
	private JMenuItem jmenuitemExit, jmenuitemAbout;
	
	private JLabel jlbOutput;

	private JPanel jplMaster;
	private JPanel jplControl;
	private JPanel jplExtra = null;
	private JPanel jplButtons;
	
	/*
	 * Font(String name, int style, int size) creates a new Font from the specified name, style and point size.
	 */
	private final Font f12 = new Font("Times New Roman", 0, 12);
	private final Font f121 = new Font("Times New Roman", 1, 12);
	
	// Constructors
	
	/**
	 * Constructs a new basic graphical view for the specified calculator model.
	 */
	public GuiBasic(BasicCalculator theCalc) {
		this.theCalc = theCalc;
		fmt = new FormatDouble();
	}
	
	/**
	 * Used by sub-classes to extend the commands displayed on the GUI.
	 * @param extra the panel containing extra GUI components.
	 */
	public void setExtra(JPanel extra) {
		jplExtra = extra;
	}
	
	/* Implementation of CalcUI interface methods */
	
	@Override
	public void start() {
		setVisible(true);
	}

	@Override
	public void displayError(String error) {
		System.out.println(error);
		JDialog eDialog = new ErrorDialog(this, "GuiCalculator Error", true, error);
		eDialog.setVisible(true);
	}
	
	@Override
	public void initialiseUI(){	
		//initialise the sub-components of the GUI.
		initialiseMenuBar();
		initialiseButtonsPanel();
		initialiseOutputPanel();
		initialiseControlPanel();	
		initialiseActionListeners();

		//Assemble the master panel
		jplMaster = new JPanel();

		if (jplExtra == null)jplExtra = new JPanel();
		
		jplMaster.setLayout(new BorderLayout());
		jplMaster.add(jplExtra, BorderLayout.NORTH);
		jplMaster.add(jplControl, BorderLayout.CENTER);
		jplMaster.add(jplButtons, BorderLayout.SOUTH);
		
		// Add components to frame
		getContentPane().add(jlbOutput, BorderLayout.NORTH);
		getContentPane().add(jplMaster, BorderLayout.SOUTH);
		
		//Set appearance
		setBackground(Color.gray);
		setSize(241, 217);
		
		theCalc.clear();
		displayTop();
		
		pack();
		setLocation(400, 250);
		setResizable(false);
		requestFocus();		
	}
	
	/** Add a WindowListener for closing this frame and ending program */
	private void initialiseActionListeners() {
		
		addWindowListener(new WindowAdapter() {
				public void windowClosed(WindowEvent e){
					System.exit(0);
				}
			}
		);
		this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);		
	}

	/* Helper methods for modularising the GUI construction */
	
	/**
	 * Initialises the control buttons panel.
	 */
	private void initialiseControlPanel() {
		jplControl = new JPanel();
		jplControl.setLayout(new GridLayout(1, 5, 2 ,2));
		jplControl.add(new CalculatorButton("Enter", Color.black));
		jplControl.add(new CalculatorButton("Fix", Color.black));
		jplControl.add(new CalculatorButton("Erase", Color.black));
		jplControl.add(new CalculatorButton("CE", Color.black));
		jplControl.add(new CalculatorButton("C", Color.black));		
	}

	/**
	 * Initialises the output display panel.
	 */
	private void initialiseOutputPanel() {
		jlbOutput = new JLabel("0");
		jlbOutput.setHorizontalTextPosition(JLabel.RIGHT);
		jlbOutput.setBackground(Color.WHITE);
		jlbOutput.setOpaque(true);
	}

	/**
	 * Initialise the numeric, accumulator and arithmetic operations buttons
	 * panel.
	 */
	private void initialiseButtonsPanel() {
		// Create panel and set layout manager for a 5 by 4 grid
		jplButtons = new JPanel();			// container for JButtons
		jplButtons.setLayout(new GridLayout(6, 4, 2, 2));
		
		//Add buttons to keypad panel starting at top left
		// top row - A-clr, A-sto, A-plus, A-rcl
		jplButtons.add(new CalculatorButton("A-clr", Color.magenta));
		jplButtons.add(new CalculatorButton("A-sto", Color.magenta));
		jplButtons.add(new CalculatorButton("A-plus", Color.magenta));
		jplButtons.add(new CalculatorButton("A-rcl", Color.magenta));
		// 2nd row - sqrt, +/-, x^2, 1/x
		jplButtons.add(new CalculatorButton("sqrt", Color.red));
		jplButtons.add(new CalculatorButton("+/-", Color.red));
		jplButtons.add(new CalculatorButton("x^2", Color.red));
		jplButtons.add(new CalculatorButton("1/x", Color.red));
		// 3rd row - 7, 8, 9, /
		jplButtons.add(new CalculatorButton("7", Color.blue));
		jplButtons.add(new CalculatorButton("8", Color.blue));
		jplButtons.add(new CalculatorButton("9", Color.blue));
		jplButtons.add(new CalculatorButton("/", Color.red));
		// 4th row - 4, 5, 6, *
		jplButtons.add(new CalculatorButton("4", Color.blue));
		jplButtons.add(new CalculatorButton("5", Color.blue));
		jplButtons.add(new CalculatorButton("6", Color.blue));
		jplButtons.add(new CalculatorButton("*", Color.red));
		// 5th row - 1, 2, 3, -
		jplButtons.add(new CalculatorButton("1", Color.blue));
		jplButtons.add(new CalculatorButton("2", Color.blue));
		jplButtons.add(new CalculatorButton("3", Color.blue));
		jplButtons.add(new CalculatorButton("-", Color.red));
		// 6th row - 0, ., pi, +
		jplButtons.add(new CalculatorButton("0", Color.blue));
		jplButtons.add(new CalculatorButton(".", Color.blue));
		jplButtons.add(new CalculatorButton("\u03c0", Color.green));
		jplButtons.add(new CalculatorButton("+", Color.red));
	}

	/**
	 * Initialise the menu bar.
	 */
	private void initialiseMenuBar(){
		jmenuFile = new JMenu("File");
		jmenuFile.setFont(f121);
		jmenuFile.setMnemonic(KeyEvent.VK_F);
		
		jmenuitemExit = new JMenuItem("Exit");
		jmenuitemExit.setFont(f12);
		jmenuitemExit.setAccelerator(KeyStroke.getKeyStroke( KeyEvent.VK_X, ActionEvent.CTRL_MASK));
		jmenuitemExit.addActionListener(this);
		
		jmenuFile.add(jmenuitemExit);
		
		jmenuHelp = new JMenu("Help");
		jmenuHelp.setFont(f121);
		jmenuHelp.setMnemonic(KeyEvent.VK_H);

		jmenuitemAbout = new JMenuItem("About Calculator");
		jmenuitemAbout.setFont(f12);
		jmenuitemAbout.addActionListener(this);
		
		jmenuHelp.add(jmenuitemAbout);
		
		JMenuBar mb = new JMenuBar();
		mb.add(jmenuFile);
		mb.add(jmenuHelp);
		setJMenuBar(mb);
	} 
	
	// Perform action
	public void actionPerformed(ActionEvent e){
	   
		if(e.getSource() == jmenuitemAbout){
			JDialog dlgAbout = new CustomABOUTDialog(this);
			dlgAbout.setVisible(true);
		}else if(e.getSource() == jmenuitemExit){
			System.exit(0);
		}	
	}
	
	/**
	 * Processes a button press.  This method can be over-ridden by
	 * sub-classes that wish to support extended operations.
	 * @param cmd
	 */
	protected void processButtonPress(String cmd) {
		//display manipulation buttons
		if (isNumber(cmd)) 						addDigitToDisplay(cmd);
		else if (cmd.equalsIgnoreCase("."))     addDecimalPoint();
		else if (cmd.equalsIgnoreCase("Erase")) processErase();
		
		//delegate to operation processing.
		else processOperation(cmd);
	}
	
	protected void processOperation(String cmd){
		try {
			//Unary operations
			if (cmd.equalsIgnoreCase("sqrt"))   theCalc.sqrt();
			else if (cmd.equalsIgnoreCase("+/-"))    theCalc.sign();
			else if (cmd.equalsIgnoreCase("x^2"))    theCalc.square();
			else if (cmd.equalsIgnoreCase("1/x"))    theCalc.invert();
			else if (cmd.equalsIgnoreCase("A-clr"))  theCalc.Aclear();
			else if (cmd.equalsIgnoreCase("A-sto"))  theCalc.Astore();
			else if (cmd.equalsIgnoreCase("A-plus")) theCalc.Aplus();
			else if (cmd.equalsIgnoreCase("A-rcl"))  theCalc.Arecall();
			else if (cmd.equalsIgnoreCase("fix"))
				try {
					int n = (int)(theCalc.pop() + 0.00001);
					fmt.setPlaces(n);
				} catch (CalculatorException ex) {
					displayError("empty stack for fix");
				}
			//Binary Operations	
			else if (cmd.equals("+")) theCalc.plus();
			else if (cmd.equals("-")) theCalc.minus();
			else if (cmd.equals("*")) theCalc.times();
			else if (cmd.equals("/")) theCalc.divide();
			
			//Constants
			else if (cmd.equalsIgnoreCase("\u03c0")) theCalc.enter(Math.PI);
			
			//Other commands     
			else if (cmd.equalsIgnoreCase("Enter")) theCalc.enter(getDisplayString());
			else if (cmd.equalsIgnoreCase("C"))     theCalc.clear();
			else if (cmd.equalsIgnoreCase("CE"))    /* do nothing except display top*/;
			displayTop();
		} catch (CalculatorException ex) {
			displayError(ex.toString());
		}
	}
	
	/**
	 * Utility method for checking if a token can be formatted as a double number.
	 * @param buf the token to check
	 * @return true if the buf token can be formatted as a double value.
	 */
	private boolean isNumber(String buf) {
		try {
			Double.valueOf(buf);
			return true;
		} catch (Exception ex){
			return false;
		}
	}
	
	/**
	 * Set the display to the value at the top of the calculator stack.
	 */
	protected void displayTop() {
		try {
			setDisplayString(fmt.format(theCalc.top()));
		} catch (CalculatorException ex) {
			setDisplayString("(empty stack)");
		}
		clearOnNextDigit = true;
	}
	
	/**
	 * Set the value of the display to the specified string.
	 * @param s the value to set on the display
	 */
	private void setDisplayString(String s){
		jlbOutput.setText(s);
	}

	/**
	 * @return the current value on the display.
	 */
	private String getDisplayString (){
		return jlbOutput.getText();
	}

	/**
	 * Adds an extra digit to the display
	 * @param digit - a single character string in the range 0-9.
	 */
	private void addDigitToDisplay(String digit){
		if (clearOnNextDigit) setDisplayString("");

		String inputString = getDisplayString();

		if ((!(inputString.equals("0") && digit.equals("0")))  && inputString.length() < MAX_INPUT_LENGTH){
			setDisplayString(inputString + digit);
		}
		clearOnNextDigit = false;
	}

	/**
	 * Add a decimal point to the display.
	 */
	private void addDecimalPoint(){
		if (clearOnNextDigit) {
			setDisplayString("0");
			clearOnNextDigit = false;
		}
		String inputString = getDisplayString();
	
		// If the input string already contains a decimal point, don't
		//  do anything to it.
		if (inputString.indexOf(".") < 0)
			setDisplayString(new String(inputString + "."));
	}
	
	private void processErase() {
		int length = getDisplayString().length();
		if (length < 2) {
			setDisplayString("0");
			clearOnNextDigit = true;
		} else {
			setDisplayString(getDisplayString().substring(0, length-1));
			clearOnNextDigit = false;
		}
	}
	
	/**Inner utility class for calculator buttons.*/
    class CalculatorButton extends JButton implements ActionListener {
		private static final long serialVersionUID = 5863454040813598922L;
		private String theOp;

		public CalculatorButton(String text, Color c) {
            super.setText(text);
            theOp = text;
            addActionListener(this);
            setForeground(c);
        }

        public void actionPerformed(ActionEvent e){
            processButtonPress(theOp);
        }
    }	
}
