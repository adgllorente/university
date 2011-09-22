package oose2.ex1b.tests;

import static org.junit.Assert.*;

import oose2.ex1b.CountryList;

import org.junit.Before;
import org.junit.Test;

public class CountryListTest {

	private CountryList list;
	
	private String[] in1  = new String [] {"a.b.e", "a.b.d", "a.b.c", "f", "a.b.e","dcs.gla.ac.uk","dcs.gla.ac.uk","dcs.gla.ac.uk","dcs.gla.ac.uk" };

	private String out1 = 
		"e          2\n"+
		"d          1\n"+
		"c          1\n"+
		"f          1\n"+
		"uk         4\n";
	
	private String sorted1 = 
		"c          1\n"+
		"d          1\n"+
		"f          1\n"+
		"e          2\n"+
		"uk         4\n";
	
	private String sortedDesc = 
		"uk         4\n"+
		"e          2\n"+
		"d          1\n"+
		"c          1\n"+
		"f          1\n";
	
	@Before
	public void setUp() throws Exception {
		list = new CountryList();
		for (String host: in1) list.increment(host);
	}

	@Test
	public void testCountryList() {
		assertEquals(out1,list.toString());		
	}

	@Test
	public void testSortByCount() {
		CountryList sorted = list.sortByCount();
		assertEquals(sorted1,sorted.toString());
	}
	
	@Test
	public void testSortByCountDesc() {
		CountryList sorted = list.sortByCountDesc();
		assertEquals(sortedDesc,sorted.toString());
	}
}