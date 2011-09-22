package oose2.ex2.model.tests;

import static oose2.ex2.model.tests.TestData.double1;
import static oose2.ex2.model.tests.TestData.double10;
import static oose2.ex2.model.tests.TestData.double2;
import static oose2.ex2.model.tests.TestData.double50;
import static oose2.ex2.model.tests.TestData.epsilon;
import static org.junit.Assert.assertEquals;
import oose2.ex2.model.CalculatorException;
import oose2.ex2.model.ExtendedCalculator;

import org.junit.Before;
import org.junit.Test;

/**
 * Extends the basic tests 
 * @author tws
 *
 */
public class ExtendedCalculatorTest extends BasicCalculatorTest{

	/** Provides an interface to the extended features of the calculator under test */
	private ExtendedCalculator extCalc;
	
	@Before
	@Override
	public void setUp() throws Exception {
		extCalc = new ExtendedCalculator();
		//Make sure that the basic functionality of the extended calculator
		//hasn't been broken.
		theCalc = extCalc;
	}

	@Test
	public final void testFahr() throws CalculatorException{
		
		extCalc.enter(double10);
		extCalc.fahr();
		Double result = extCalc.pop();
		assertEquals(double50,result,epsilon);
	}

	@Test
	public final void testCelc() throws CalculatorException{
		extCalc.enter(double50);
		extCalc.celc();
		Double result = extCalc.pop();
		assertEquals(double10,result,epsilon);
	}

	@Test
	public final void testSwap() throws CalculatorException{
		extCalc.enter(double1);
		extCalc.enter(double2);
		extCalc.swap();
		Double result1 = extCalc.pop();
		Double result2 = extCalc.pop();
		
		assertEquals(double1,result1,epsilon);
		assertEquals(double2,result2,epsilon);
	}

}
