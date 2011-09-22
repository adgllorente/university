package ac4;

import java.util.ArrayList;
import java.util.Iterator;

public class Net {

	//Params
	public static int totalNodes = 0;
	public static int infinity = 9999;
	enum enumStatus{NEW, STABLE, UNSTABLE};
	enumStatus status;
	ArrayList<Node> nodes;
	ArrayList<Link> links;
	
	//Methods
	public Net() {
		this.nodes = new ArrayList<Node>();
		this.links = new ArrayList<Link>();
		status = enumStatus.NEW;
	}
	
	/**
	 * Inserts a new Node n in the net
	 * @param n
	 */
	public boolean insertNode(String id){
		Node n = new Node(id, this.nodes.size());
		return this.nodes.add(n);
	}
	
	/**
	 * Inserts a new Link l in the net. Of the link is already in the net is updated
	 * @param l
	 */
	public boolean insertLink(String node1, String node2, int cost){
		
		//Finding nodes
		Node n1=null, n2=null;
		n1 = findNode(node1);
		n2 = findNode(node2);
		
		//Checking if the link exists
		Iterator<Link> lIterator = this.links.iterator();
		while(lIterator.hasNext()){
			Link l1 = lIterator.next();
			if((l1.n1.index == n1.getIndex() && l1.n2.index == n2.getIndex()) || (l1.n1.index == n2.getIndex() && l1.n2.index == n1.getIndex())){
				//If the link exists cost is updated
				l1.cost = cost;
				
				//Cost is updated in routetable
				n1.getR().insert(n2.getIndex(), cost, n2.getIndex());
				n2.getR().insert(n1.getIndex(), cost, n1.getIndex());
				
				this.status = enumStatus.UNSTABLE;
				return true;
			}
		}
		if(n1 != null && n2 != null){
			Link l = new Link(n1, n2, cost);
			return this.links.add(l);
		}else{
			return false;
		}
	}
	
	/**
	 * Simulate current net
	 */
	public void simulate(int iteration){
		for(int i=0;i<iteration;i++){
			if(i==0 && this.status == enumStatus.NEW){
				//Initializing routetables
				Iterator<Link> j = this.links.iterator();
				while(j.hasNext()){
					Link l = j.next();
					l.n1.updateRoutetable(l.n2.getIndex(), l.cost, l.n2.getIndex());
					l.n2.updateRoutetable(l.n1.getIndex(), l.cost, l.n1.getIndex());
				}
			}else{
				ArrayList<Routetable> routetableBackup = new ArrayList<Routetable>();
				
				//Applying the algorithm and saving changes in the backups
				Iterator<Node> k = this.nodes.iterator();
				while(k.hasNext()){
					
					Node n1 = k.next();
					Routetable r1 = n1.getR();
					
					//Backuping the routetable
					Routetable backup = new Routetable();
					for(int ibackup=0;ibackup<totalNodes;ibackup++){
						for(int jbackup=0;jbackup<totalNodes;jbackup++){
							backup.insert(ibackup, r1.getEntry(ibackup, jbackup), jbackup);
						}
					}
					routetableBackup.add(backup);
					
					for(int iCurrent=0;iCurrent<totalNodes;iCurrent++){
						
						if(iCurrent != n1.getIndex()){
							
							if(r1.getEntry(iCurrent, iCurrent) != 0){
								
								//Obtaining new Node
								Node n2 = this.nodes.get(iCurrent);
								Routetable r2 = n2.getR();
								
								//Checking new values
								for(int iNew=0;iNew<totalNodes;iNew++){
									
									//Not current node
									if(iNew != n1.getIndex()){
										
										int valueN2 = r2.getMinRow(iNew);
										
										//Saving new minimum value to new node
										if(valueN2 != Net.infinity){
											
											//Calculating new value
											int newValue = valueN2 + r1.getEntry(n2.getIndex(), n2.getIndex());
											routetableBackup.get(n1.getIndex()).insert(iNew, newValue, n2.getIndex());
										}
									}
								}
							}
						}
					}
				}
				//Copying new distances to current routetables
				for(int currentID=0;currentID<routetableBackup.size();currentID++){
					this.nodes.get(currentID).setR(routetableBackup.get(currentID));
				}
			}
			System.out.println("###ITERATION: " + i);
			//Show routetables
			showRouteTables();
		}
		this.status = enumStatus.STABLE;
	}
	
	/**
	 * Show routetables
	 */
	public void showRouteTables(){
		Iterator<Node> i = this.nodes.iterator();
		while(i.hasNext()){
			Node n = i.next();
			System.out.println(n.getId());
			n.getR().show(this.nodes);
		}
	}
	
	/**
	 * Update one link cost
	 * @param name
	 * @param newCost
	 */
	public void updateLink(String name, int newCost){
		
	}
	
	@Override
	public String toString() {
		String s = "";
		return s;
	}
	
	/**
	 * Show current net
	 */
	public void show() {
		System.out.println("## Nodes");
		System.out.println(this.nodes.toString());
		System.out.println("## Links");
		System.out.println(this.links.toString());
	}

	/**
	 * Calculate best route between two nodes
	 * @param n1
	 * @param n2
	 */
	public void bestRoute(String n1, String n2) {
		Node source = findNode(n1);
		Node destiny = findNode(n2);
		System.out.println("From: " + n1 + " To: " + n2 + " Distance: " + source.getR().getMinRow(destiny.getIndex()));
	}

	/**
	 * Find a node into the Node array
	 * @param n1
	 * @return
	 */
	private Node findNode(String n1) {
		Iterator<Node> i = this.nodes.iterator();
		while(i.hasNext()){
			Node n = i.next();
			if(n.equals(n1)){
				return n;
			}
		}
		return null;
	}
	
	
}
