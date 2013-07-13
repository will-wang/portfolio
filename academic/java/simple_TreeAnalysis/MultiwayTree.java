/**
* This class creates a (2,4) tree
*
* MultiwayTree.java
* CS1332 Fall 2009 Final Project
* @author Nianzu Wang (GTid: 902228976)
* Email: wangn89@gmail.com
* I worked on this assignment by myself using only course materials.
*/


public class MultiwayTree {

	MultiwayNode root = null; //creates a root node with nothing in it

	public MultiwayNode getRoot() { //returns root
		
		return this.root;
	}

	public boolean isEmpty() { //tests if tree is empty by testing if root is empty
	
		return(this.root.isEmptyNode());
	}

	public boolean find(int numToFind) { //finds a given number
	
		if(this.root == null) { //if empty returns false
		
			return false;
		}
		
		else {
		
			return find(numToFind, getRoot()); //else pass value and root to private find
		}
	}

	private boolean find(int numToFind, MultiwayNode node) { //searches through the children for numToFind
		
		int[] data = node.getData(); //stores the data of the node
		int index = 0; //initializes an index
		boolean result = false; //initialize result as false until found
	
		while(data[index] != -1 && index < 3) { //search through the data unless empty or at end
			
			if(numToFind > data[index]) {
			
				index++;
			}
			
			else if(numToFind == data[index]) { //return true if found
			
				result = true;
			}
			
			else if(numToFind < data[index] && index == 0) { //passes first child if numToFind is less than first data
				
				node = node.getFirstChild();
				return(find(numToFind, node));
			}
			
			else if(numToFind < data[index] && index == 1 ) { //passes second child if numToFind is between first and second data
			
				node = node.getSecondChild();
				return(find(numToFind,node));
			}
			
			else if(numToFind < data[index] && index == 2 ) { //passes third child if numToFind is between second and third data
				
				node = node.getThirdChild();
				return(find(numToFind,node));
			}	
			
			else if(numToFind > data[index] && index == 2 ) { //passes fourth child if numToFind greater than third data
				
				node = node.getFourthChild();
				return(find(numToFind,node));
			}
		}
		
		return result;
	}
	
	public void insert(int newNum) {
	
	}
	
	public static void main(String[] args) {
	
	}
}
