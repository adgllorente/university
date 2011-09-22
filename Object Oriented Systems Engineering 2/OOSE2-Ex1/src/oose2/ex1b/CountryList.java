/*
 * ArrayList to hold Country references
 */
package oose2.ex1b;

import java.util.ArrayList;
import java.util.Iterator;

public class CountryList {
	
	private ArrayList<Country> countries = new ArrayList<Country>(100);
	private int totalCount;
	private int nextAvailable;

	/*
	 * return the country code from the address, lower cased
	 */
	private String countryCode(String address) {
		int j = address.lastIndexOf('.') + 1;
		String cc = address.substring(j);
		return cc.toLowerCase();
	}
	/*
	 * find the index into the CountryList that corresponds to
	 * the country code passed in the arguments
	 * 
	 * if not found, returns -1, otherwise returns a number
	 * in the range of 0 .. nextAvailable-1
	 */
	public int findIndex(String countryCode) {
		int i;
		
		for (i = 0; i < this.nextAvailable; i++) {
			Country c1 = this.countries.get(i);
			if (c1.countryCode().equals(countryCode))
				return i;
		}
		return -1;
	}
	
	/*
	 * perform binary insertion of `c' into `this' based upon c.compareTo
	 */
	private void binInsert(Country c) {
		int left, right, mid = 0, n;
		Country temp = null;
		
		n = this.nextAvailable;
		if (n == 0) {	// empty list, just add and return
			this.countries.add(c);
			this.nextAvailable++;
			return;
		}
		left = 0;
		right = n - 1;
		temp = this.countries.get(left);
		if (c.compareTo(temp) < 0) {
			this.countries.add(left, c);
			this.nextAvailable++;
			return;
		}
		temp = this.countries.get(right);
		if (c.compareTo(temp) > 0) {
			this.countries.add(n, c);
			this.nextAvailable++;
			return;
		}

		// first time through left < right
		while (left <= right) {
			mid = (left + right) / 2;
			temp = this.countries.get(mid);
			int cv = c.compareTo(temp);
			if (cv < 0)
				right = mid - 1;
			else if (cv > 0)
				left = mid + 1;
			else {			// Country already in list
				return;
			}
		}
		this.countries.add(left, c);
		this.nextAvailable++;
	}
	
	/*
	 * perform binary decreasing insertion of `c' into `this' based upon c.compareTo
	 */
	private void binInsertDesc(Country c) {
		int left, right, mid = 0, n;
		Country temp = null;
		
		n = this.nextAvailable;
		if (n == 0) {	// empty list, just add and return
			this.countries.add(c);
			this.nextAvailable++;
			return;
		}
		left = 0;
		right = n - 1;
		temp = this.countries.get(left);
		if (c.compareTo(temp) > 0) {
			this.countries.add(left, c);
			this.nextAvailable++;
			return;
		}
		temp = this.countries.get(right);
		if (c.compareTo(temp) < 0) {
			this.countries.add(n, c);
			this.nextAvailable++;
			return;
		}

		// first time through left < right
		while (left <= right) {
			mid = (left + right) / 2;
			temp = this.countries.get(mid);
			int cv = c.compareTo(temp);
			if (cv < 0)
				right = mid - 1;
			else if (cv > 0)
				left = mid + 1;
			else {			// Country already in list
				return;
			}
		}
		this.countries.add(left, c);
		this.nextAvailable++;
	}
	
	// CONSTRUCTORS
	/**
	 * create an empty CountryList
	 * 
	 */
	public CountryList() {
		this.totalCount = 0;
		this.nextAvailable = 0;
	}
	
	// METHODS
	/**
	 * increment the count associated with a particular Internet address
	 * if it is not already in the list, new Country entry is added
	 * 
	 * @param	address	the Internet address
	 */
	public void increment(String address) {
		String cc = this.countryCode(address);
		int i = findIndex(cc);
		if (i != -1) {
			Country c1 = this.countries.get(i);
			c1.increment();
		} else {
			i = this.nextAvailable++;
			Country c1 = new Country(cc);
			this.countries.add(i, c1);
		}
		this.totalCount++;
	}
		
	/**
	 * Return copy of `this', sorted by increasing count
	 */
	public CountryList sortByCount() {
		CountryList sorted = new CountryList();
		for (int i = 0; i < this.nextAvailable; i++)
			sorted.binInsert(new Country(this.countries.get(i)));
		sorted.totalCount = this.totalCount;
		return sorted;
	}
	
	/**
	 * Return copy of `this', sorted by decreasing count
	 */
	public CountryList sortByCountDesc() {
		CountryList sorted = new CountryList();
		for (int i = 0; i < this.nextAvailable; i++)
			sorted.binInsertDesc(new Country(this.countries.get(i)));
		sorted.totalCount = this.totalCount;
		return sorted;
	}
	
	/**
	 * Returns the number of unique country codes held by this country list.
	 * 
	 */
	public int countryCount(){
		return this.countries.size();
	}
	
	/**
	 * Returns the country at the specified index in the list or null
	 * if the index is not in use.
	 */
	public Country getCountry(int index){
		return countries.get(index);
	}

	public String toString() {
		int i;
		StringBuffer buf = new StringBuffer();
		
		for (i = 0; i < this.nextAvailable; i++) {
			Country c = this.countries.get(i);
			buf.append(c.toString());
			buf.append('\n');
		}
		return buf.toString();
	}
}