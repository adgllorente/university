package oose2.ex1b.tests;

import static org.junit.Assert.*;

import oose2.ex1b.Date;

import org.junit.Before;
import org.junit.Test;

public class DateTest {

	Date d1;
	Date d2;
	Date d3;
	
	String d1str;
	String d2str;
	String d3str;
	String d4str;
	String d5str;
	String d6str;
	
	@Before
	public void setUp() throws Exception {
		d1 = new Date(29, 1, 1952);
		d2 = new Date(29, 11, 1967);
		d3 = new Date(1, 1, 2099);
		d1str = "29/01/1952";
		d2str = "29/02/1956";
		d3str = "28/02/1956";
		d4str = "29/02/2000";
		d5str = "31/01/2000";
		d6str = "30/04/2000";
	}

	//Make sure that the date objects were initialised
	@Test
	public void testDateIntIntInt1() {
		assertNotNull(d1);
		assertNotNull(d2);
		assertNotNull(d3);

	}
	
	//Test that invalid inputs to the int,int,int constructor are rejected (1-5).
	
	@Test(expected=IllegalArgumentException.class)
	public void testDateIntIntInt2() {
		new Date(29, 1, 1899);
	}
	
	@Test(expected=IllegalArgumentException.class)
	public void testDateIntIntInt3() {
		new Date(31, -1, 1900);
	}
	
	@Test(expected=IllegalArgumentException.class)
	public void testDateIntIntInt4() {
		new Date(31, 13, 1900);
	}
	
	@Test(expected=IllegalArgumentException.class)
	public void testDateIntIntInt5() {
		new Date(32, 1, 1900);
	}
	
	@Test(expected=IllegalArgumentException.class)
	public void testDateIntIntInt6() {
		new Date(30, 2, 1900);
	}
	
	@Test(expected=IllegalArgumentException.class)
	public void testDateIntIntInt7() {
		new Date(29, 2, 1957);
	}
	
	@Test(expected=IllegalArgumentException.class)
	public void testDateIntIntInt8() {
		new Date(29, 2, 1900);
	}
	
	@Test //Leap year
	public void testDateString1() {
		Date d1 = new Date(d2str);
		assertEquals(d2str, d1.toString());
	}
	
	@Test //Normal February
	public void testDateString2() {
		Date d1 = new Date(d3str);
		assertEquals(d3str, d1.toString());
	}
	
	@Test //Leap year
	public void testDateString3() {
		Date d1 = new Date(d4str);
		assertEquals(d4str, d1.toString());
	}
	
	@Test //Long month
	public void testDateString4() {
		Date d1 = new Date(d5str);
		assertEquals(d5str, d1.toString());
	}
	
	@Test //Short month
	public void testDateString5() {
		Date d1 = new Date(d6str);
		assertEquals(d6str, d1.toString());
	}

	//Test the String constructor
	@Test
	public void testDateString() {
		Date d1 = new Date(d1str);
		assertEquals(d1str, d1.toString());
	}
	
	//Test that date formatting is working
	@Test
	public void testToString() {
		assertEquals("Yields", d1str, d1.toString());
	}

	//Before is an ordering over dates.
	@Test
	public void testBefore() {		
		assertTrue(d1.before(d2));
		assertTrue(d2.before(d3));		
		assertTrue(d1.before(d3));
		assertFalse(d2.before(d1));
		assertFalse(d2.before(d2));
	}
}
