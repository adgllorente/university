package oose2.ex1b.tests;


import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.InputStream;
import java.io.PrintWriter;

import oose2.ex1b.Date;
import oose2.ex1b.LogStats;

import org.junit.Before;
import org.junit.Test;

public class TimedLogStatsTest {

	private LogStats logStats;
	private Date start;
	private Date end;
	
	@Before
	public void setUp() throws Exception {
		logStats = new LogStats();
		start = new Date(01,02,1900);
		end = new Date(01,02,2008);
	}
	
	@Test
	/**
	 * Test LogStats multiplying by 2 each time the number of different countries and the number of lines.
	 */
	public void testInsertionTiming(){
		//Be careful to re-initisalise the logStats variable for each 
		//timing loop.
		logStats = new LogStats();
		doLargeCountryInsert(1000,1000);
		logStats = new LogStats();
		doLargeCountryInsert(2000, 2000);
		logStats = new LogStats();
		doLargeCountryInsert(4000, 4000);
		logStats = new LogStats();
		doLargeCountryInsert(8000, 8000);
		logStats = new LogStats();
		doLargeCountryInsert(16000, 16000);
		logStats = new LogStats();
		doLargeCountryInsert(32000, 32000);
	}
	
	@Test
	/**
	 * Test LogStats multiplying by 2 each time the number of lines but with the same different countries.
	 */
	public void testInsertionTimingEqualCountries(){
		//Be careful to re-initisalise the logStats variable for each 
		//timing loop.
		logStats = new LogStats();
		doLargeCountryInsert(1000,1000);
		logStats = new LogStats();
		doLargeCountryInsert(1000, 2000);
		logStats = new LogStats();
		doLargeCountryInsert(1000, 4000);
		logStats = new LogStats();
		doLargeCountryInsert(1000, 8000);
		logStats = new LogStats();
		doLargeCountryInsert(1000, 16000);
		logStats = new LogStats();
		doLargeCountryInsert(1000, 32000);
	}
	
	private void doLargeCountryInsert(int numberOfLines, int numberOfEntries){
		// Mark the start time.
		long startTime = System.currentTimeMillis();
		
		InputStream log = generateLargeLogInputStream(numberOfLines,numberOfEntries);
		
		logStats.doProcessing(start, end, log);
		
		//Mark the end time.
		long elapsedTime = System.currentTimeMillis() - startTime;
		
		System.out.println(String.format(
				"Lines: %d, Entries: %d, Elapsed time: %d.%03d seconds",
				numberOfLines, numberOfEntries, elapsedTime/1000, elapsedTime%1000));
	}

	
	/**
	 * Prepares a simulated file input stream representing a log file.
	 * @param nccodes number of unique country codes.
	 * @param nentries number of entries.
	 * @return
	 */
	private InputStream generateLargeLogInputStream(int nccodes, int nentries) {
		
		String letters = new String("abcdefghijklmnopqrstuvwxyz");
		
		int entPerCc = (nentries - 1) / nccodes + 1;
		
		ByteArrayOutputStream baos = new ByteArrayOutputStream();
		PrintWriter pw = new PrintWriter(baos);
		
		char[] ccode = new char[5];
		int i, j, k, l, m, n;
		for (i=0; i < 26; i++) {
			ccode[0] = letters.charAt(i);
			for (j = 0; j < 26; j++) {
				ccode[1] = letters.charAt(j);
				for (k = 0; k < 26; k++) {
					ccode[2] = letters.charAt(k);
					for (l = 0; l < 26; l++) {
						ccode[3] = letters.charAt(l);
						for (m = 0; m < 26; m++) {
							ccode[4] = letters.charAt(m);
							for (n = 0; n < entPerCc; n++) {
								pw.println("01/01/2000 first.second." + new String(ccode));
								if (--nentries <= 0) {
									pw.close();
									return new ByteArrayInputStream(baos.toByteArray());
								}
							}
						}
					}
				}
			}
		}
		return new ByteArrayInputStream(baos.toByteArray());
	}


}
