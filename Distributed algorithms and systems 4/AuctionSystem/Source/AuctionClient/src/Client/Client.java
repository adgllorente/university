package Client;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.rmi.Naming;
import java.rmi.RMISecurityManager;
import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;
import java.util.ArrayList;
import java.util.Iterator;
import Server.Bidder;

/**
 * @author Adrián Gómez Llorente
 * @matriculation 0904327G
 */

public class Client{

	/**
	 * @param args
	 */
	
	public static void main(String[] args) {
		Bidder bidder = null;
		//System.setSecurityManager(new RMISecurityManager());
		try {
			bidder = (Bidder) Naming.lookup("//localhost/bidder");
			
			do {
				/** Display menu */
				System.out.println("-- Welcome to the auction service --");
				System.out.println("-- ");
				System.out.println("-- 1: Add auction");
				System.out.println("-- 2: View auctions");
				System.out.println("-- 3: Bid auction");
				System.out.println("-- 4: View bids");
				System.out.println("-- 0: Exit");
				BufferedReader buffer = new BufferedReader(
						new InputStreamReader(System.in));
				int op = 0;
				try {
					op = Integer.valueOf(buffer.readLine());
				} catch (IOException e) {
					e.printStackTrace();
				}

				switch (op) {
				case 1:
					try {
						System.out.print("Name: ");
						String name = (String)buffer.readLine();
						System.out.print("Value: ");
						float value = Float.valueOf(buffer.readLine());
						bidder.addAuction(name, value);
						System.out.println("Auction added succesfully!");
						System.out.println("Press intro to continue");
						buffer.readLine();
					} catch (RemoteException e) {
						e.printStackTrace();
					}
					break;
				case 2:
					try {
						ArrayList<String> auctions = bidder.getAuctions();
						Iterator<String> i = auctions.iterator();
						while(i.hasNext()){
							System.out.println(i.next());
						}
					} catch (RemoteException e) {
						e.printStackTrace();
					}
					System.out.println("Press intro to continue");
					buffer.readLine();
					break;
				case 3:
					try {
						System.out.println("Insert id: ");
						int id = Integer.valueOf(buffer.readLine());
						if(bidder.checkAuctionId(id)){
							System.out.println("Introduce you email: ");
							String email = buffer.readLine();
							System.out.println("Introduce value: ");
							float value = Float.valueOf(buffer.readLine());
							if(bidder.checkAuctionId(id)){
								if(bidder.bidAuction(id, value, email)){
									System.out.println("Bid done correctly");
								}else{
									System.out.println("Your bid has been reached");
								}
							}else{
								System.out.println("Id incorrect");
							}
						}else{
							System.out.println("Id incorrect");
						}
					} catch (RemoteException e) {
						e.printStackTrace();
					}
					break;
				case 4:
					System.out.println("Insert id: ");
					int id = Integer.valueOf(buffer.readLine());
					String bidders = bidder.getBidders(id);
					System.out.println(bidders);
					buffer.readLine();
					break;
				case 0:
					System.exit(0);
					break;
				default:
					System.out.println("Option is not correct");
				}
				System.out.print("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
			} while (true);
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
	
	
}
