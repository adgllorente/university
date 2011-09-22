package oose2.ex1b.tests;


import static org.junit.Assert.*;

import java.io.ByteArrayOutputStream;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStream;
import java.util.Random;

import oose2.ex1b.Country;
import oose2.ex1b.CountryList;
import oose2.ex1b.Date;
import oose2.ex1b.LogStats;

import org.junit.Before;
import org.junit.Test;

public class LogStatsTest {
	
	private LogStats logStats;
	private Date start;
	private Date end;

	@Before
	public void setUp() throws Exception {
		logStats = new LogStats();
		start = new Date(01, 01, 2001);
		end = new Date(31, 12, 2002);
	}
	
	//Test the small log file against a known test oracle's output.
	@Test
	public void testSmallLog(){
		String inputFile = "logs/small.log";
		String expectedOutputFile = "logs/small-2001.01.01-2002.12.31.out";
		
		InputStream inputIS = getISForFile(inputFile);
			
		CountryList countries = logStats.doProcessing(start, end, inputIS);
		String expectedOutput = new String(getFileContents(expectedOutputFile));
		
		assertEquals(expectedOutput,countries.toString());
	}
	
	//Obtaining an oracle for large tests is often difficult, so instead, 
	//heuristics have to be used.  The heuristic here is that any two randomly
	//selected country codes from a sorted list should adhere to the compareTo
	//specification.
	@Test
	public void testLargeLogWhenSorted(){
		String inputFile = "logs/big.log";
		int samples = 100;
				
		InputStream inputIS = getISForFile(inputFile);
			
		CountryList countries = logStats.doProcessing(start, end, inputIS);
		
		Random r = new Random();
		
		for (int i = 0 ; i < samples; i++){
			int index1 = r.nextInt(countries.countryCount());
			int index2 = r.nextInt(countries.countryCount());
			
			Country c1 = countries.getCountry(index1);
			Country c2 = countries.getCountry(index2);
						
			assertTrue( (index1 == index2 && c1.compareTo(c2) == 0 ) ||
					    (index1 <  index2 && c1.compareTo(c2)  < 0 ) ||
					    (index1 >  index2 && c1.compareTo(c2)  > 0 )    );
		}	
	}
	
	
	// UTILITY METHODS FOR PREPARING TEST DATA

	private static byte[] getFileContents(String fname){
		InputStream is = getISForFile(fname);
		
		ByteArrayOutputStream baos = new ByteArrayOutputStream();
		
		try {
			while (is.available() > 0){
				int b = is.read();
				//Throw away additional carriage return. 
				if (b!='\r')baos.write(b);
			}
		} catch (IOException e) {
			fail("Couldn't read data from file ["+fname+"].");
		}
		
		return baos.toByteArray();
	}
	
	private static InputStream getISForFile(String fname){
		InputStream is = null;
		try {
			 is = new FileInputStream(fname);
		} catch (FileNotFoundException e) {
			fail("File not found ["+fname+"].");
		} 
		return is;
	}

}
