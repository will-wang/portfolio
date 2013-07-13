/**
* The purpose of this class is to create a node for a (2,4) tree
*
* MultiwayNode.java
* CS1332 Fall 2009 Final Project
* @author Nianzu Wang (GTid: 902228976)
* Email: wangn89@gmail.com
* I worked on this assignment by myself using only course materials.
*/


public class MultiwayNode {
	
	private int[] data = new int[4]; //creates an int array of max length 4 to hold the data in each node
	private MultiwayNode[] branch = new MultiwayNode[5]; //creates a node array of max length 5 to hold the children of each node
	
	public MultiwayNode() { //empty constructor
		
	}
	
	public MultiwayNode(int dat) { //constructor that takes an int data as a param
		
		this.data[0] = dat; //sets it as the first element in the data array
	}
	
	public int[] getData() { //returns the data array
	
		return this.data;
	}
		
	public void setData(int[] newData) { //sets the data array of the node as the int array newData
	
		this.data = newData;
	}
	
	public boolean isEmptyNode() { //checks if the node is empty, returns boolean
	
		boolean empty = true; //initialize it at true
		
		for(int index = 0; index < this.data.length; index++) { //test if there is data and sets empty as false if there is
			
			if(data[index] != -1) {
			
				empty = false;
			}
		}
		
		return empty;
	}
	
	public int getNumChildren() { //returns number of children
	
		int Num = 0; //initialize a count at 0
		
		for(int index = 0; index < this.branch.length; index++) { //tests if the branches or children are empty nodes or not
		
			if(branch[index].isEmptyNode() != true) { //if it is not an empty node, increment the count by 1
				
				Num++;
			}
		}
		
		return Num;
	}
	
	public MultiwayNode getFirstChild() { //return first child
		
		return branch[0];
	}
	
	public void setFirstChild(MultiwayNode newFirstChild) { //sets first child as the node newFirstChild
	
		branch[0] = newFirstChild;
	}
	
	public MultiwayNode getSecondChild() { //return second child
	
		return branch[1];
	}

	public void setSecondChild(MultiwayNode newSecondChild) { //sets second child as the node newSecondChild
	
		branch[1] = newSecondChild;
	}
	
	public MultiwayNode getThirdChild() { //return third child
	
		return branch[2];
	}
	
	public void setThirdChild(MultiwayNode newThirdChild) { //sets third child as the node newThirdChild
	
		branch[2] = newThirdChild;
	}
	
	public MultiwayNode getFourthChild() { //return fourth child
	
		return branch[3];
	}
	
	public void setFourthChild(MultiwayNode newFourthChild) { //sets fourth child as the node newFourthChild
	
		branch[3] = newFourthChild;
	}
	
	public MultiwayNode getFifthChild() { //return fifth child
	
		return branch[4];
	}
	
	public void setFifthChild(MultiwayNode newFifthChild) { //sets fifth child as the node newFifthChild
	
		branch[4] = newFifthChild;
	}
}
