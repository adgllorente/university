package ac4;

import java.util.ArrayList;
import java.util.Vector;

/**
 * This class create a routetable and offer all operations needed to work with it.
 * The routetable is as shown below:
 *            			OUTGOING
 *   			 ----------------------     
 *   			 |
 *   DESTINATION |		DISTANCES
 *   			 |
 * @author Adrian Gomez (0904327G)
 */
public class Routetable {
	
	//Params
	int[][] entries;
	
	//Methods
	public Routetable() {
		this.entries = new int[99][99];
		for(int i=0;i<99;i++){
			for(int j=0;j<99;j++){
				this.entries[i][j] = 0;
			}
		}
	}
	
	/**
	 * Insert a new entry in the routetable
	 * @param destination: Destination to next node
	 * @param distance: Distance to next node
	 * @param outgoing: Outgoing port
	 * @return boolean with the result
	 */
	public boolean insert(int destination, int distance, int outgoing){
		this.entries[destination][outgoing] = distance;
		return true;
	}
	
	/**
	 * Returns minimum value of a row of the routetable
	 * @param position: Position to get
	 * @return
	 */
	public int getMinRow(int destination){
		int min = Net.infinity;
		for(int i=0;i<Net.totalNodes;i++){
			if(this.entries[destination][i] != 0 && this.entries[destination][i] < min){
				min = this.entries[destination][i];
			}
		}
		return min;
	}
	
	/**
	 * Returns a column of the routetable
	 * @param outgoing
	 * @return
	 */
	public Vector<Integer> getColumn(int outgoing){
		Vector<Integer> v = new Vector<Integer>();
		for(int i=0;i<Net.totalNodes;i++){
			v.add(this.entries[i][outgoing]);
		}
		return v;
	}

	/**
	 * Show routetable in three columns
	 * @param nodes
	 */
	public void show(ArrayList nodes) {
		System.out.println("DESTINATION\tDISTANCE\tOUTGOING\n");
		for(int i=0;i<Net.totalNodes;i++){
			for(int j=0;j<Net.totalNodes;j++){
				if(this.entries[i][j] != 0){
					System.out.println(((Node)nodes.get(i)).getId() + "\t\t" +  this.entries[i][j] + "\t\t" + ((Node)nodes.get(j)).getId() + "\n");
				}
			}
		}
	}
	
	public int getEntry(int i, int j){
		return this.entries[i][j];
	}
}
