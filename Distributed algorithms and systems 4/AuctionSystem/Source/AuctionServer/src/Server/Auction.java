package Server;

/**
 * @author Adrián Gómez Llorente
 * @matriculation 0904327G
 */

import java.util.Collections;
import java.util.Date;
import java.util.HashMap;
import java.util.Iterator;
import java.util.List;
import java.util.Set;

public class Auction{

	/** Parameters */
	int id;
	float value;
	String name;
	Date end;
	HashMap<String, Float> bidders;

	/** Methods */

	public Auction(int id, float value, String name, Date end){
		this.id = id;
		this.value = value;
		this.name = name;
		this.end = end;
		this.bidders = new HashMap<String, Float>();
	}

	public synchronized boolean addBidder(String email, float value){
		
		//If there isn't bids
		if(this.bidders.size() == 0){
			this.bidders.put(email, value);	
			return true;
		}
		
		//Has reached maximum
		boolean higher = true;
		Iterator<Float> i = this.bidders.values().iterator();
		float f = 0;
		while(i.hasNext() && higher){
			f = i.next();
			higher = value > f;
		}
		if(higher){
			Date now = new Date(System.currentTimeMillis());
			if(now.before(this.getEnd())){
				this.bidders.put(email, value);
				return true;
			}
		}
		return false;
	}
	
	/**
	 * @return the bidders
	 */
	public HashMap<String, Float> getBidders(){
		return bidders;
	}
	
	/**
	 * @return the id
	 */
	public int getId() {
		return id;
	}

	/**
	 * @return the value
	 */
	public float getValue() {
		return value;
	}

	/**
	 * @return the name
	 */
	public String getName() {
		return name;
	}

	/**
	 * @return the end
	 */
	public Date getEnd() {
		return end;
	}
	
	public String toString(){
		String a = this.getId() + ": " + this.getName() + " - " + this.getValue() + "GBP" + " (" + this.getEnd().toString() + ")";
		return a;
	}
	
	protected void informBidders(){
		Set<String> bids = this.bidders.keySet();
		Iterator<String> i = bids.iterator();
		
		//Looking for maximum
		String maxBidder = "";
		float max = 0;
		while(i.hasNext()){
			String a = i.next();
			float maxpos = this.bidders.get(a);
			if(maxpos > max){
				max = maxpos;
				maxBidder = a;
			}
		}
		
		//Minimum reached
		if(this.value < max){
			SendEmail sender = new SendEmail(maxBidder, "About bid " + this.getName(), "You are the maximum bidder!");
			
			System.out.println("Bid: \"" + this.getName() + "\" finished. Winner: " + maxBidder);
			
			Iterator<String> n = this.bidders.keySet().iterator();
			String biddersEmails[] = new String[this.bidders.size()];
			int m = 0;
			while(n.hasNext()){
				biddersEmails[m] = n.next();
				m++;
			}
			sender = new SendEmail(biddersEmails, "About bid " + this.getName(), "bid has finished with winner");
		}else{
			Iterator<String> n = this.bidders.keySet().iterator();
			String biddersEmails[] = new String[this.bidders.size()];
			int m = 0;
			while(n.hasNext()){
				biddersEmails[m] = n.next();
				m++;
			}
			SendEmail sender = new SendEmail(biddersEmails, "About bid " + this.getName(), "Minimum bid value has not been reached");
			System.out.println("Bid: \"" + this.getName() + "\" no minimum reached.");
		}
	}
}
