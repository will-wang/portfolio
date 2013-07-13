/**
* BSTNode.java
* CS1332 Fall 2009 Final Project
* @author Nianzu Wang (GTid: 902228976)
* Email: wangn89@gmail.com
* I worked on this assignment by myself using only course materials.
*/

//This class is meant to set up and provide generic information and methods of Binary Search Trees.

public class BSTNode<K extends Comparable<K>> { 

	public BSTNode<K> leftchild; //declares left child
	public BSTNode<K> rightchild; //declares right child
	public K data; //holds data of type K
	
	public BSTNode (K data) { //contructor with a K type parameter
	
		this.data = data; //creates a BSTNode with the given data
	}
	
	public BSTNode(BSTNode<K> current) { //constructor with a BSTNode<K> parameter. Sets its left, right children and data, to currently referenced ones.
	
		leftchild = current.leftchild; 
		rightchild = current.rightchild;
		data = current.data;
	}
	
	public K getData() {
	
		if (data == null) {
		
			return null;
		}
		
		else {
		
			return data;
		}
	}
	
	public void setData (K newValue) {
	
		data = newValue;
	}
	
	public boolean isEmptyNode() {
	
		return data == null;
	}
	
	public BSTNode<K> getLeftChild() {
	
		if (leftchild != null) {
		
			return leftchild;
		}
		
		else {
		
			return null;
		}
	}
	
	public void setLeftChild(BSTNode<K> newLeftChild) {
	
		if (newLeftChild == null) {
		
			leftchild = null;
		}
		
		else {
		
			leftchild = newLeftChild;
		}
	}
	
	public BSTNode<K> getRightChild() {
	
		if (rightchild != null) {
		
			return rightchild;
		}
		
		else {
		
			return null;
		}
	}
	
	public void setRightChild(BSTNode<K> newRightChild) {
	
		if (newRightChild == null) {
		
			rightchild = null;
		}
		
		else {
		
			rightchild = newRightChild;
		}
	}
}