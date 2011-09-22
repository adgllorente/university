package ac4;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStreamReader;

public class Logic {
	
	//Params
	static Net net;
	
	public Logic() {
		net = new Net();
	}
	
	public static void main(String[] args) {
		int option = 0;
		Logic log = new Logic();
		
		while(true){
			System.out.println("Choose an option:");
			System.out.println("1: Parse net");
			System.out.println("2: Simulate net");
			System.out.println("3: Change values");
			System.out.println("4: Show bestroute");
			System.out.println("5: Show net");
			System.out.println("6: Show routetables");
			System.out.println("0: Exit");
			
			BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
			
			try {
				option = Integer.parseInt(in.readLine());
				switch(option){
				case 1: //Parsing the net
					System.out.println("Type the path");
					String name = in.readLine();
					log.parser(name);
					break;
				case 2://Simulating the net
					System.out.println("Number of iterations");
					int iterations = Integer.parseInt(in.readLine());
					net.simulate(iterations);
					break;
				case 3://Change values
					System.out.print("What link do you want to change? (ex: link a;b;10)(infinity = 9999): ");
					String s = in.readLine();
					
					//Parsing new link
					String regexLinks = "link[ ]*[a-zA-Z0-9]*;[a-zA-Z0-9]*;[0-9]*";
					if(s.matches(regexLinks)){
						//Is a link
						String subLine = s.replaceAll("link[ ]*", "").trim().trim();
						String node1 = subLine.split(";")[0];
						String node2 = subLine.split(";")[1];
						int cost = Integer.parseInt(subLine.split(";")[2]);
						
						//Inserting the link
						net.insertLink(node1, node2, cost);
						System.out.println("Links updated: " + node1 + "<----" + cost + "---->" + node2);
					}else{
						System.out.println("Link incorrect");
					}
					break;
				case 4://Show best route
					System.out.print("Node 1: ");
					String n1 = in.readLine();
					System.out.print("Node2: ");
					String n2 = in.readLine();
					net.bestRoute(n1, n2);
					break;
				case 5://Show the net
					net.show();
					break;
				case 6://Show routetables
					net.showRouteTables();
					break;
				case 0://Exit
					System.exit(0);
				default:
					System.out.println("Incorrect option");
					break;
				}
			} catch (NumberFormatException e) {
				e.printStackTrace();
			} catch (IOException e) {
				e.printStackTrace();
			}
		}
	}
	
	private boolean parser(String name) {
		//REGEX
		String regexNodes = "node[ ]*[a-zA-Z0-9]*";
		String regexLinks = "link[ ]*[a-zA-Z0-9]*;[a-zA-Z0-9]*;[0-9]*";
		
		//Cleaning the net
		net = new Net();
		
		File f = new File(name);
		if(f.exists()){
			try {
				//Loading the buffer
				BufferedReader in = new BufferedReader(new InputStreamReader(new FileInputStream(f)));
				String line = null;
				
				while((line = in.readLine()) != null){
					line = line.toLowerCase();
					if(line.matches(regexNodes)){
						//Is a node
						String nodeName = line.replaceAll("node[ ]*", "").trim();
						
						//Inserting the node
						net.insertNode(nodeName);
						System.out.println("Adding node: " + nodeName );
					}else if(line.matches(regexLinks)){
						//Is a link
						String subLine = line.replaceAll("link[ ]*", "").trim().trim();
						String node1 = subLine.split(";")[0];
						String node2 = subLine.split(";")[1];
						int cost = Integer.parseInt(subLine.split(";")[2]);
						
						//Inserting the link
						net.insertLink(node1, node2, cost);
						System.out.println("Adding link: " + node1 + "<----" + cost + "---->" + node2);
					}
				}
			} catch (FileNotFoundException e) {
				e.printStackTrace();
			} catch (IOException e) {
				e.printStackTrace();
			}
			net.totalNodes = net.nodes.size();
			return true;
		}else{
			return false;
		}
	}
}
