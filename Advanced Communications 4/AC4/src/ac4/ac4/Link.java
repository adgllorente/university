package ac4;

public class Link {
	
	//Params
	Node n1;
	Node n2;
	int cost; //Cost equal -1 is fail
	
	//Methods
	public Link(Node n1, Node n2, int cost) {
		this.n1 = n1;
		this.n2 = n2;
		this.cost = cost;
	}
	
	public Node getN1() {
		return n1;
	}
	
	public void setN1(Node n1) {
		this.n1 = n1;
	}
	
	public Node getN2() {
		return n2;
	}
	
	public void setN2(Node n2) {
		this.n2 = n2;
	}
	
	public int getCost() {
		return cost;
	}
	
	public void setCost(int cost) {
		this.cost = cost;
	}
	
	@Override
	public String toString() {
		String s = n1.getId() + "<----" + cost + "---->" + n2.getId()+"\n";
		return s;
	}
}
