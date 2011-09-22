package oose2.ex1b.tests;

import static org.junit.Assert.*;

import java.util.Random;

import oose2.ex1b.Country;

import org.junit.Before;
import org.junit.Test;

public class CountryTest {

	private Country c1;
	private Country c2;
	private Country c3;
	
	private String c1code = "foo";
	private String c2code = "bar";
	
	@Before
	public void setUp() throws Exception {
		c1 = new Country(c1code);
		c2 = new Country(c2code);
		c3 = new Country(c1code);
	}

	@Test
	public void testCountryString1() {
		assertNotNull(c1);
		assertNotNull(c2);
	}

	
	@Test(expected=NullPointerException.class)
	public void testCountryString2() {
		new Country((String)null);
	}

	//Copying of a country object
	@Test
	public void testCountryCountry1() {
		//Note that assertEquals will not work here
		//because the equals method in Country does not
		//override the Object.equals(Object) method.
		assertTrue(c1.equals(new Country(c1)));
	}
	
	@Test(expected=NullPointerException.class)
	public void testCountryCountry2() {
		new Country((Country)null);
	}


	@Test
	public void testEqualsCountry() {
		assertTrue(c1.equals(c1));
		assertTrue(c1.equals(new Country(c1)));
		assertTrue(c3.equals(c1));		
		
		//Make sure that count differences are ignored.
		c3.increment();
		assertTrue(c3.equals(c1));

	}
	
	@Test
	public void testIncrementAndCount() {
		c1.increment();
		assertEquals(2,c1.count());
		
		int count = new Random().nextInt(1000);
		for (int i = 0; i < count; i++)
			c2.increment();
		
		assertEquals(count+1,c2.count());
	}

	@Test
	public void testCountryCode() {
		assertEquals(c1code,c1.countryCode());
	}

	@Test
	public void testCompareTo() {
		assertEquals(0,c1.compareTo(c1));
		
	}

	@Test
	public void testToString() {
		assertEquals(String.format("%-5s%7d",c1code,1),c1.toString());
	}

}
