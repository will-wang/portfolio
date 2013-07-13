/**
* GenericBST.java
* CS1332 Fall 2009 Final Project
* @author Nianzu Wang (GTid: 902228976)
* Email: wangn89@gmail.com
* I worked on this assignment by myself using only course materials.
*/

//This class is meant to create and provide methods for a Generic Binary Search Tree.

public class GenericBST<K extends Comparable<K>> {

	protected BSTNode<K> root = null; //creates a root node with nothing in it
	protected String s = ""; //start the storage for output
	
	public GenericBST() { //empty constructor
	
	}
	
	public BSTNode<K> getRoot() {
	
		if (root != null) {
		
			return root;
		}
		
		else {
		
			return null;
		}
	}
	
	public boolean isEmpty() {
	
		if (root == null) {
		
			System.out.println("true");
			return true;
		}
		
		else {
		
			System.out.println("false");
			return false;
		}
	}
	
	public void insert(K c) {
	
		BSTNode<K> add = new BSTNode(c); //save the given data into a node named add
		BSTNode<K> current = root; //create a reference to root called current
		BSTNode<K> parent = null; //create an empty node parent for reference
		
		while (current != null) { //this while loop tests where on the tree the data should go
		
			parent = current;
			
			if (c.compareTo(current.getData()) < 0) {
			
				current = current.getLeftChild();
			}
			
			else if (c.compareTo(current.getData()) > 0) {
			
				current = current.getRightChild();
			}
			
			else {
				break;
			}
		}
		
		if (parent != null && c.compareTo(parent.getData()) < 0) { //determines whether node should go in left child
		
			parent.setLeftChild(add);
		}
		
		else if (parent != null && c.compareTo(parent.getData()) > 0) { //determines whether node should go in right child
		
			parent.setRightChild(add);
		}
		
		else {
		
			root = add; //makes the node the root if root is empty
		}
	}
	
	public boolean remove(K c) {
		
		//BSTNode<K> current = root;
		//BSTNode<K> parent = null;
		
		//while (current != null || c.compareTo(current.getData()) != 0) {
		
			//parent = current;
			
			//if (c.compareTo(current.getData()) < 0 && current.getLeftChild() != null) {
			
				//current = current.getLeftChild();
			//}
			
			//else if (c.compareTo(current.getData()) > 0 && current.getRightChild() != null) {
			
				//current = current.getRightChild();
			//} 
		//}
		
		//if (c.compareTo(current.getData()) == 0 && current.getLeftChild() == null) {
		
			//parent.setLeftChild(null);
			//System.out.println("true");
			//return true;
		//}
		
		//else if (c.compareTo(current.getData()) == 0 && current.getRightChild() == null) {
		
			//parent.setRightChild(null);
			//System.out.println("true");
			//return true;
		//}

		//else {
		
			//System.out.println("Either the data could not be found, or it was found at an internal branch.");
			//System.out.println("false");
			return false;
		//}
	}
	
	public boolean find (K c) {
	
		BSTNode<K> current = root; //creates a node current and points it to root
		
		while (current != null) { //this while loop determines which way to look for data, given the node looked at isnt null
		
			if (c.compareTo(current.getData()) != 0) {
			
				if (c.compareTo(current.getData()) < 0) {
			
				current = current.getLeftChild();
				}
			
				else if (c.compareTo(current.getData()) > 0) {
			
				current = current.getRightChild();
				}
			}
			
			else if (c.compareTo(current.getData()) == 0) { //if it is found, return true
				return true;
			}
		} //if not return false
		return false;
	}
	
	public String preOrderTraversal() { //given method in BinarySearchTree. Started at root, returns string of data traversed.
	
		preOrder(root);
		System.out.println(s);
		return s;
	}
	
	public String preOrder(BSTNode<K> node) { //created to run actual traversing separate from called method.
		
		if (node != null) { //as long as the node being looked at isnt null, append the data and a space, then look left (repeat), then look right (repeat).
		
			s += (node.getData() + " ");
			preOrder(node.getLeftChild());
			preOrder(node.getRightChild());
		}
		return s;
	}
	
	// public static void main (String[] args) { //main method where methods are tested with Integer types.
// 	
// 		GenericBST test = new GenericBST();
// 		test.insert(10);
// 		test.insert(5);
// 		test.insert(15);
// 		test.insert(2);
// 		test.insert(20);
// 		test.insert(7);
// 		test.insert(13);
// 		test.preOrderTraversal();
// 		test.getRoot();
// 		test.isEmpty();
// 		test.find(7);
// 		test.find(50);
// 		test.remove(2);
// 		
// 	}
}
	
	
			