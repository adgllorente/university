package Server;

import java.rmi.Remote;
import java.rmi.RemoteException;
import java.util.ArrayList;

import javax.management.Notification;

/**
 * @author Adrián Gómez Llorente
 * @matriculation 0904327G
 */

public interface Bidder extends Remote {
	public ArrayList<String> getAuctions() throws RemoteException;

	public void addAuction(String name, float value) throws RemoteException;

	public boolean bidAuction(int id, float value, String email) throws RemoteException;
	
	public boolean checkAuctionId(int id) throws RemoteException;
	
	public String getBidders(int id) throws RemoteException;
}