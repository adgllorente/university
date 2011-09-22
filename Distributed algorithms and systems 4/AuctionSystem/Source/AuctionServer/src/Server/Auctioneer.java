package Server;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.rmi.RMISecurityManager;
import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;
import java.util.ArrayList;
import java.util.Date;
import java.util.HashMap;
import java.util.Iterator;
import java.util.Vector;

import javax.management.Notification;

/**
 * @author Adrián Gómez Llorente
 * @matriculation 0904327G
 */

public class Auctioneer extends UnicastRemoteObject implements Bidder  {

	/** Parameters */
	static HashMap<Integer, Auction> auctions;
	static int bidID;

	public Auctioneer() throws RemoteException{
		auctions = new HashMap<Integer, Auction>();
		bidID = 0;
	}

	@Override
	public synchronized void addAuction(String name, float value) throws RemoteException {
		bidID++;
		Auction a = new Auction(bidID, value, name, new Date(System.currentTimeMillis() + 60000));
		auctions.put(bidID, a);
	}

	@Override
	public synchronized boolean bidAuction(int id, float value, String email) throws RemoteException {
		return auctions.get(id).addBidder(email, value);
	}

	@Override
	public ArrayList<String> getAuctions() throws RemoteException {
		ArrayList<String> a = new ArrayList<String>();
		Iterator<Auction> i = auctions.values().iterator();
		while(i.hasNext()){
			a.add(i.next().toString());
		}
		return a;
	}

	/**
	 * Clean obsolete auctions
	 */
	public synchronized static void cleaner() {
		Iterator<Auction> i = auctions.values().iterator();
		boolean cont = true;
		while (i.hasNext() && cont) {
			Auction a = i.next();
			Date now = new Date(System.currentTimeMillis());
			if (now.after(a.end)){
				a.informBidders();
				i.remove();
			}else{
				cont = false;
			}
		}
	}

	@Override
	public synchronized boolean checkAuctionId(int id) throws RemoteException {
		return auctions.get(id) != null;
	}

	@Override
	public synchronized String getBidders(int id) throws RemoteException {
		HashMap<String, Float> bidders = auctions.get(id).getBidders();
		return bidders.toString();
	}
}