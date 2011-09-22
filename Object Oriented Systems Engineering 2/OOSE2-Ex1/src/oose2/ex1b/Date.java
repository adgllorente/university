/*
 * represent dates in the international calendar
 *
 * of the form dd/mm/yyyy
 */
package oose2.ex1b;

import java.util.*;

public class Date {

	private int day;
	private int month;
	private int year;

	
	/**
	 * Validates a date using leap years and normal years.
	 * 
	 */
	private boolean validate() {
		// Leap year
		boolean leap = this.year % 4 == 0
				&& (this.year % 100 != 0 || this.year % 400 == 0);
		if (this.month == 2 && leap && this.day <= 29)
			return true;
		// Not leap year
		else if (this.month == 2 && !leap && this.day <= 28)
			return true;
		else if ((this.day >= 1 && this.day <= 31)
				&& (this.month == 1 || this.month == 3 || this.month == 5
						|| this.month == 7 || this.month == 8
						|| this.month == 10 || this.month == 12)
				&& (this.year >= 1900)) {
			return true;
		} else if ((this.day >= 1 && this.day <= 31)
				&& (this.month == 4 || this.month == 6 || this.month == 9 || this.month == 11)
				&& this.year >= 1900) {
			return true;
		} else {
			return false;
		}
	}

	// CONSTRUCTORS
	/**
	 * create a date from the day, month, and year parameters
	 * 
	 * @param day
	 *            numeric value for day
	 * @param month
	 *            numeric value for month
	 * @param year
	 *            numeric value for year
	 * @exception IllegalArgumentException
	 *                - date not valid
	 */
	public Date(int day, int month, int year) throws IllegalArgumentException {
		IllegalArgumentException ex = new IllegalArgumentException(
				"Invalid date");
		this.day = day;
		this.month = month;
		this.year = year;
		if (!this.validate()) {
			throw ex;
		}
	}

	/**
	 * create a date from a string of the form dd/mm/yyyy
	 * 
	 * @param str
	 *            String of the form dd/mm/yyyy
	 * @exception InputMismatchException
	 *                - string formatted incorrectly
	 * @exception IllegalArgumentException
	 *                - date not valid
	 */
	public Date(String str) throws IllegalArgumentException,
			InputMismatchException {
		Scanner input = new Scanner(str);
		InputMismatchException ex = new InputMismatchException(
				"Date format error");
		input.useDelimiter("/");
		if (!input.hasNextInt())
			throw ex;
		this.day = input.nextInt();
		if (!input.hasNextInt())
			throw ex;
		this.month = input.nextInt();
		if (!input.hasNextInt())
			throw ex;
		this.year = input.nextInt();
		if (!this.validate())
			throw new IllegalArgumentException("Invalid date");
		;
	}

	// METHODS
	/**
	 * Determine if this comes before the supplied date
	 * 
	 * @param dt
	 *            the supplied date
	 * @return true/false if this < date
	 */
	public boolean before(Date dt) {
		if (this.year < dt.year)
			return true;
		if (this.year == dt.year) {
			if (this.month < dt.month)
				return true;
			if (this.month == dt.month)
				if (this.day < dt.day)
					return true;
		}
		return (false);
	}

	public String toString() {
		return String.format("%02d/%02d/%04d", this.day, this.month, this.year);
	}
}