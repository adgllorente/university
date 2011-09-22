package ac4;

public class Node {

	//Parameters
	String id;
	int index;
	Routetable r;
	
	//Methods
	public Node(String id, int index) {
		this.id = id;
		this.index = index;
		this.r = new Routetable();
	}
	
	@Override
	public String toString() {
		String s = "Name: " + this.id;
		return s;
	}
	
	@Override
	public boolean equals(Object obj) {
		if(obj != null){
			String n = (String)obj;
			return this.id.compareTo(n) == 0;
		}
		return false;
	}

	public String getId() {
		return id;
	}

	public void setId(String id) {
		this.id = id;
	}

	public Routetable getR() {
		return r;
	}

	public void setR(Routetable r) {
		for(int i=0;i<Net.totalNodes;i++){
			for(int j=0;j<Net.totalNodes;j++){
				this.r.insert(i, r.getEntry(i, j), j);
			}
		}
	}
	
	public int getIndex() {
		return index;
	}

	public void setIndex(int index) {
		this.index = index;
	}

	/**
	 * Update Routetable with new information given
	 * @param destination
	 * @param distance
	 * @param outgoing
	 */
	public void updateRoutetable(int destination, int distance, int outgoing){
		this.r.insert(destination, distance, outgoing);
	}
}