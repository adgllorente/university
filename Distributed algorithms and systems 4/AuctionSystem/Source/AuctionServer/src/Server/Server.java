package Server;

import java.rmi.Naming;
import java.rmi.registry.LocateRegistry;

public class Server {

	/**
	 * @param args
	 */

	public Server() {
	}

	public synchronized static void main(String[] args) {
		new Server();
		
		try {
			
			//Starting RMI
			LocateRegistry.createRegistry(1099);
			
			// Configuring RMI
			//System.setProperty("java.rmi.server.codebase",
							//"file:/C:/Users/KuvE/Documents/develop/AuctionServer/bin/Server/");

			// Starting remote object
			Auctioneer a = new Auctioneer();
			Bidder bidder = (Bidder)a;
			Naming.bind("//localhost/bidder", bidder);
			System.out.println("Hello!");
		} catch (Exception e) {
			e.printStackTrace();
		}
		
		//Cleaner
		class cleanerDaemon implements Runnable{
			
			Thread cleaner;
			public cleanerDaemon() {
				cleaner = new Thread(this);
				cleaner.setDaemon(true);
				cleaner.start();
			}
			
			@Override
			public void run() {
				// TODO Auto-generated method stub
				while(true){
					Auctioneer.cleaner();
				}
			}
		}
		
		cleanerDaemon cleaner = new cleanerDaemon();
	}
}
