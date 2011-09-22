package oose2.ex1b;

import oose2.ex1b.CountryList;

import java.util.Scanner;
import java.io.*;

public class LogStats
{
	/**
	 * Program to read web log files, accumulating statistics
	 * for log entries associated with each country code (final
     * field in a domain name) that fall within the specified
	 * date interval; prints out country code followed by number of
	 * entries
	 * 
	 * @param	args	args[0] = begindate, args[1]= enddate, args[2] = logfilename
	 */
	public static void main(String[] args){
		
		if (args.length < 3) {
			System.err.println("Usage: LogStats begindate enddate logfilename");
			System.exit(1);
		}
		Date start = new Date(args[0]);
		Date end = new Date(args[1]);
		
		String file = new String (args[2]);
		InputStream log = null;
		try {
			log = new FileInputStream(file);
		} catch (FileNotFoundException e){
			System.err.println("Cannot open the file" + file);
			System.exit(1);
		}

		CountryList sortedList = new LogStats().doProcessing(start,end,log);

		System.out.println(String.format("Statistics for %s in the date interval [%s, %s]", file, start, end));
		System.out.println(sortedList);
	}
	
	public CountryList doProcessing(Date start, Date end, InputStream log){
		Scanner inputScanner = new Scanner(log);
		CountryList theList = new CountryList();
		
		while (inputScanner.hasNext()) {
			String date = inputScanner.next();
			String address = inputScanner.next();
			Date dt = new Date(date);
			if (! (dt.before(start) || end.before(dt))) {
				theList.increment(address);
			}
		}
		return theList.sortByCount();
			
	}
}