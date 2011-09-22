package oose2.ex2.model.tests;

import static org.junit.Assert.*;
import static oose2.ex2.model.tests.TestData.*;
import oose2.ex2.model.CalculatorException;
import oose2.ex2.model.ScientificCalculator;
import org.junit.Before;
import org.junit.Test;

public class ScientificCalculatorTest extends BasicCalculatorTest{

	private ScientificCalculator sciCalc;

	@Before
	public void setUp() throws Exception{
		sciCalc = new ScientificCalculator();
		// make sure calculator is pristine
		theCalc = sciCalc;
	}

	@Test
	public void testLn() throws CalculatorException {
		sciCalc.enter(double1);
		sciCalc.ln();
		Double result = sciCalc.pop();
		assertEquals(double0, result, epsilon);
	}

	@Test
	public void testExp() throws CalculatorException {
		sciCalc.enter(double2);
		sciCalc.exp();
		Double result = sciCalc.pop();
		assertEquals(Math.exp(double2), result, epsilon);
	}

	@Test
	public void testPow() throws CalculatorException {
		sciCalc.enter(double2);
		sciCalc.enter(double2);
		sciCalc.pow();
		Double result = sciCalc.pop();
		assertEquals(double4, result, epsilon);
	}

	@Test
	public void testRad() throws CalculatorException {
		sciCalc.enter(90.0);
		sciCalc.rad();
		Double result = sciCalc.pop();
		assertEquals(Math.PI/double2, result, epsilon);
	}

	@Test
	public void testSin() throws CalculatorException {
		sciCalc.enter(90.0);
		sciCalc.rad();
		Double result = sciCalc.pop();
		sciCalc.enter(result);
		sciCalc.sin();
		Double result1 = sciCalc.pop();
		assertEquals(double1, result1);
	}

	@Test
	public void testCos() throws CalculatorException {
		sciCalc.enter(90.0);
		sciCalc.rad();
		Double result = sciCalc.pop();
		sciCalc.enter(result);
		sciCalc.cos();
		Double result1 = sciCalc.pop();
		assertEquals(double0, result1, 1.0e-15);
	}

	@Test
	public void testTan() throws CalculatorException {
		sciCalc.enter(45.0);
		sciCalc.rad();
		Double result = sciCalc.pop();
		sciCalc.enter(result);
		sciCalc.tan();
		Double result1 = sciCalc.pop();
		assertEquals(double1, result1, 1.0e-15);
	}

}
