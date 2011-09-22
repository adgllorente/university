package oose2.ex2.model.tests;

/**
 * JUnit test class for Basic Calculator
 * 
 * Tests functional aspects of the BasicCalculator class - uses the JUnit 4 framework.
 * @author tws
 */

import static org.junit.Assert.*;

import static oose2.ex2.model.tests.TestData.*;

import org.junit.Before;
import org.junit.Test;

import oose2.ex2.model.BasicCalculator;
import oose2.ex2.model.CalculatorException;

public class BasicCalculatorTest {

	protected BasicCalculator theCalc;

	@Before
	public void setUp() throws Exception{
		theCalc = new BasicCalculator();
		// make sure calculator is pristine
		theCalc.clear();
	}

	/* Test pushing values onto the calculator stack. */
	
	@Test
	public void testEnter1() throws CalculatorException {
		theCalc.enter(string9);
		Double result = theCalc.pop();
		
		assertEquals(double9,result,epsilon);
	}

	@Test
	public void testEnter2() throws CalculatorException {
		theCalc.enter(double2);
		Double result = theCalc.pop();
		assertEquals(double2,result,epsilon);
	}
	
	/* Test behaviour of operations on an empty stack */

	@Test(expected = CalculatorException.class)
	public void testEmptyStackPlus() throws CalculatorException {
		theCalc.plus();
	}

	@Test(expected = CalculatorException.class)
	public void testEmptyStackMinus() throws CalculatorException {
		theCalc.minus();
	}

	@Test(expected = CalculatorException.class)
	public void testEmptyStackTimes() throws CalculatorException {
		theCalc.times();
	}

	@Test(expected = CalculatorException.class)
	public void testEmptyStackDivide() throws CalculatorException {
		theCalc.divide();
	}

	@Test(expected = CalculatorException.class)
	public void testEmptyStackSign() throws CalculatorException {
		theCalc.sign();
	}

	@Test(expected = CalculatorException.class)	
	public void testEmptyStackInvert() throws CalculatorException {
		theCalc.invert();
	}

	@Test(expected = CalculatorException.class)
	public void testEmptyStackSquare() throws CalculatorException {
		theCalc.square();
	}

	@Test(expected = CalculatorException.class)
	public void testEmptyStackSqrt() throws CalculatorException {
		theCalc.sqrt();
	}

	@Test(expected = CalculatorException.class)
	public void testEmptyStackTop() throws CalculatorException {
		theCalc.top();
	}
	
	@Test(expected = CalculatorException.class)
	public void testEmptyStackPop() throws CalculatorException {
		theCalc.pop();
	}

	@Test(expected = CalculatorException.class)
	public void testMissingOperandPlus() throws CalculatorException {
		theCalc.enter(string9);
		theCalc.plus();
	}

	@Test(expected = CalculatorException.class)
	public void testMissingOperandMinus() throws CalculatorException {
		theCalc.enter(string9);
		theCalc.minus();
	}

	@Test(expected = CalculatorException.class)
	public void testMissingOperandTimes() throws CalculatorException {
		theCalc.enter(string9);
		theCalc.times();
	}

	@Test(expected = CalculatorException.class)
	public void testMissingOperandDivide() throws CalculatorException {
		theCalc.enter(string9);
		theCalc.divide();
	}

	@Test(expected = CalculatorException.class)
	public void testInvertZero() throws CalculatorException {
		theCalc.enter(double0);
		theCalc.invert();
	}
	
	@Test(expected = CalculatorException.class)
	public void testDivideByZero() throws CalculatorException {
		theCalc.enter(double2);
		theCalc.enter(double0);
		theCalc.divide();
	}

	@Test(expected = CalculatorException.class)
	public void testSqrtNegativeNumber() throws CalculatorException {
		theCalc.enter(doublem4);
		theCalc.sqrt();
	}

	/* Test unary operations. */
	
	@Test
	public void testSquare() throws CalculatorException {
		theCalc.enter(double2);
		theCalc.square();
		Double result = theCalc.pop();
		assertEquals(double4,result,epsilon);
	}

	@Test
	public void testSqrt() throws CalculatorException {
		theCalc.enter(double4);
		theCalc.sqrt();
		Double result = theCalc.pop();
		assertEquals(double2,result,epsilon);
	}
	
	@Test
	public void testSign() throws CalculatorException {
		theCalc.enter(double4);
		theCalc.sign();
		Double result = theCalc.pop();
		assertEquals(doublem4,result,epsilon);
	}
	
	@Test
	public void testInvert() throws CalculatorException {	
		theCalc.enter(double4);
		theCalc.invert();
		Double result = theCalc.pop();
		assertEquals(doublep25,result,epsilon);
	}

	/* Test binary operations */
	
	@Test
	public void testPlus() throws CalculatorException {
		theCalc.enter(double2);
		theCalc.enter(double2);
		theCalc.plus();
		Double result = theCalc.pop();
		assertEquals(double4,result,epsilon);
		}
	
	@Test	
	public void testMinus() throws CalculatorException {
		theCalc.enter(double0);
		theCalc.enter(double4);
		theCalc.minus();
		Double result = theCalc.pop();
		assertEquals(doublem4,result,epsilon);
	}
	
	@Test
	public void testTimes() throws CalculatorException{
		theCalc.enter(double2);
		theCalc.enter(double2);
		theCalc.times();
		Double result = theCalc.pop();
		assertEquals(double4,result,epsilon);
	}
	
	@Test
	public void testDivide() throws CalculatorException{
		theCalc.enter(double1);
		theCalc.enter(double4);
		theCalc.divide();
		Double result = theCalc.pop();
		assertEquals(doublep25,result,epsilon);
	}

	/* Test Accumulator operations */
	
	@Test(expected=CalculatorException.class)
	public void testInvalidAccumulatorIndex() throws CalculatorException {
		theCalc.enter(doublem4);
		theCalc.Aclear();
	}
	
	@Test
	public void testAccumulatorStoreRecall() throws CalculatorException {	
		theCalc.enter(double1);
		theCalc.enter(double0);
		theCalc.Astore(); // stores 1.0 in accumulator 0
		theCalc.enter(double0);
		theCalc.Arecall(); // recalls value of accumulator 0
		Double result = theCalc.pop();
		assertEquals(double1,result,epsilon);
	}
	
	@Test
	public void testAccumulatorPlus() throws CalculatorException {		
		theCalc.enter(double2);
		for (int i = 0; i < 4; i++) { // add 2 to accumulator 1 four times
			theCalc.enter(double2);
			theCalc.Aplus();
		}
		theCalc.Arecall();
		Double result = theCalc.pop();
		assertEquals(double8,result,epsilon);
	}

}
