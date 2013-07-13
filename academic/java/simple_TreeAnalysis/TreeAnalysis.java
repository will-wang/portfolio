/**
* This class tests the running time of inserting 100, 500, and 1000 values in order and randomly into
* the GenericBST and (2,4) Tree.
* This class also tests the running time of finding 100, 500, and 1000 numbers in the GenericBST and (2,4) Tree.
*
* TreeAnalysis.java
* CS1332 Fall 2009 Final Project
* @author Nianzu Wang (GTid: 902228976)
* Email: wangn89@gmail.com
* I worked on this assignment by myself using only course materials.
*/

import java.util.Random; //import Random class to generate random numbers used later

public class TreeAnalysis {
	
	public static void main (String[] args) {
		
		GenericBST insertBST1 = new GenericBST(); //create first GenericBST to test
		
		System.out.print("Adding 1-100 to a BST in increasing order: ");
		
		long insertTime1 = System.nanoTime(); //record start time
	
		for (int i = 1; i <= 100; i++) { //insert 1-100
	
			insertBST1.insert(i);	
		}
		
		long estimate1 = System.nanoTime() - insertTime1; //calculate time it took
		
		System.out.println(estimate1 + "ns");
		
		MultiwayTree insert241 = new MultiwayTree(); //create first MultiwayTree to test
		
		System.out.print("Adding 1-100 to a (2,4) tree in increasing order: ");
		
		long insertTime2 = System.nanoTime(); //record start time
		
		for (int i = 1; i <= 100; i++) { //insert 1-100
	
			insert241.insert(i);
		}
		
		long estimate2 = System.nanoTime() - insertTime2; //calculate time it took
		
		System.out.println(estimate2 + "ns");
		
		GenericBST insertBST2 = new GenericBST(); //create second BST
		
		System.out.print("Adding 1-500 to a BST in increasing order: ");
		
		long insertTime3 = System.nanoTime(); //record start time
	
		for (int i = 1; i <= 500; i++) { //insert 1-500
	
			insertBST2.insert(i);	
		}
		
		long estimate3 = System.nanoTime() - insertTime3; //calculate time
		
		System.out.println(estimate3 + "ns");
		
		MultiwayTree insert242 = new MultiwayTree(); //create second 2,4
		
		System.out.print("Adding 1-500 to a (2,4) tree in increasing order: ");
		
		long insertTime4 = System.nanoTime(); //record start time
		
		for (int i = 1; i <= 500; i++) { //insert 1-500
	
			insert242.insert(i);
		}
		
		long estimate4 = System.nanoTime() - insertTime4; //calculate time
		
		System.out.println(estimate4 + "ns");
		
		GenericBST insertBST3 = new GenericBST(); //create third BST
		
		System.out.print("Adding 1-1000 to a BST in increasing order: ");
		
		long insertTime5 = System.nanoTime(); //record start time
	
		for (int i = 1; i <= 1000; i++) { //insert 1-1000
	
			insertBST3.insert(i);	
		}
		
		long estimate5 = System.nanoTime() - insertTime5; //calculate time
		
		System.out.println(estimate5 + "ns");
		
		MultiwayTree insert243 = new MultiwayTree(); //create third 2,4
		
		System.out.print("Adding 1-1000 to a (2,4) tree in increasing order: ");
		
		long insertTime6 = System.nanoTime(); //record start time
		
		for (int i = 1; i <= 1000; i++) { //insert 1-1000
	
			insert243.insert(i);
		}
		
		long estimate6 = System.nanoTime() - insertTime6; //calculate time
		
		System.out.println(estimate6 + "ns");
		
		
		Random rand = new Random(); //initiate random generator
		
		int[] nums100 = new int[100]; //create an int array of length 100
		
		for (int i = 0; i < 100; i++) { //fill int array with random ints from 1-100
	
			nums100[i] = rand.nextInt(100) + 1;
		}
		
		GenericBST randomBST1 = new GenericBST();
		
//		 for (int i = 0; i < 100; i++) {
// 			System.out.println(nums100[i]);
// 		}
		
		System.out.print("Attempting to add 100 numbers to a BST: ");
		
		long randomTime1 = System.nanoTime();
	
		for (int num : nums100) { //inserting random 100 numbers
			
			randomBST1.insert(num);
		}
		
		long est1 = System.nanoTime() - randomTime1;
		
		System.out.println(est1 + "ns");
		
		MultiwayTree random241 = new MultiwayTree();
		
		System.out.print("Attempting to add 100 numbers to a (2,4) tree: ");
		
		long randomTime2 = System.nanoTime();
	
		for (int num : nums100) { //inserting same random 100 numbers into 2,4 tree
			
			random241.insert(num);	
		}
		
		long est2 = System.nanoTime() - randomTime2;
		
		System.out.println(est2 + "ns");
		
		int[] nums500 = new int[500]; //create an int array of length 500
		
		for (int i = 0; i < 500; i++) { //fill array with 500 random ints from 1-500
	
			nums500[i] = rand.nextInt(500) + 1;
		}
		
		GenericBST randomBST2 = new GenericBST();
		
		System.out.print("Attempting to add 500 numbers to a BST: ");
		
		long randomTime3 = System.nanoTime();
	
		for (int num : nums500) { //insert array of 500 ints
			
			randomBST2.insert(num);	
		}
		
		long est3 = System.nanoTime() - randomTime3;
		
		System.out.println(est3 + "ns");
		
		MultiwayTree random242 = new MultiwayTree();
		
		System.out.print("Attempting to add 500 numbers to a (2,4) tree: ");
		
		long randomTime4 = System.nanoTime();
	
		for (int num : nums500) { //inserting same array of 500 ints
			
			random242.insert(num);	
		}
		
		long est4 = System.nanoTime() - randomTime4;
		
		System.out.println(est4 + "ns");
		
		int[] nums1000 = new int[1000]; //create an int array of 1000 ints
		
		for (int i = 0; i < 1000; i++) { //add in 1000 random ints from 1-1000
	
			nums1000[i] = rand.nextInt(1000) + 1;
		}
		
		GenericBST randomBST3 = new GenericBST();
		
		System.out.print("Attempting to add 1000 numbers to a BST: ");
		
		long randomTime5 = System.nanoTime();
	
		for (int num : nums1000) { //insert array of 1000 ints
			
			randomBST3.insert(num);	
		}
		
		long est5 = System.nanoTime() - randomTime5;
		
		System.out.println(est5 + "ns");
		
		MultiwayTree random243 = new MultiwayTree();
		
		System.out.print("Attempting to add 1000 numbers to a (2,4) tree: ");
		
		long randomTime6 = System.nanoTime();
	
		for (int num : nums1000) { //insert same array of 1000 ints
	
			random243.insert(num);
		}
		
		long est6 = System.nanoTime() - randomTime6;
		
		System.out.println(est6 + "ns");
		
		
		int[] find100 = new int[100]; //create an int array of length 100 to find
		
		for (int i = 0; i < 100; i++) { //fill int array with random ints from 1-100
	
			find100[i] = rand.nextInt(100) + 1;
		}
		
		System.out.print("Attempting to find 100 numbers in a BST: ");
		
		long findTime1 = System.nanoTime();
		
		for (int num : find100) { //find int array of 100
			
			randomBST3.find(num);	
		}
		
		long time1 = System.nanoTime() - findTime1;
		
		System.out.println(time1 + "ns");
		
		System.out.print("Attempting to find 100 numbers in a (2,4) tree: ");
		
		long findTime2 = System.nanoTime();
		
		for (int num : find100) {
			
			random243.find(num); //find int array of 100	
		}
		
		long time2 = System.nanoTime() - findTime2;
		
		System.out.println(time2 + "ns");
		
		int[] find500 = new int[500];
		
		for (int i = 0; i < 500; i++) {
	
			find500[i] = rand.nextInt(500) + 1;
		}
		
		System.out.print("Attempting to find 500 numbers in a BST: ");
		
		long findTime3 = System.nanoTime();
		
		for (int i = 0; i < 500; i++) {
			
			randomBST3.find(find500[i]);	
		}
		
		long time3 = System.nanoTime() - findTime3;
		
		System.out.println(time3 + "ns");
		
		System.out.print("Attempting to find 500 numbers in a (2,4) tree: ");
		
		long findTime4 = System.nanoTime();
		
		for (int i = 0; i < 500; i++) {
			
			random243.find(find500[i]);	
		}
		
		long time4 = System.nanoTime() - findTime4;
		
		System.out.println(time4 + "ns");
		
		int[] find1000 = new int[1000];
		
		for (int i = 0; i < 1000; i++) {
	
			find1000[i] = rand.nextInt(1000) + 1;
		}
		
		System.out.print("Attempting to find 1000 numbers in a BST: ");
		
		long findTime5 = System.nanoTime();
		
		for (int i = 0; i < 1000; i++) {
			
			randomBST3.find(find1000[i]);	
		}
		
		long time5 = System.nanoTime() - findTime5;
		
		System.out.println(time5 + "ns");
		
		System.out.print("Attempting to find 1000 numbers in a (2,4) tree: ");
		
		long findTime6 = System.nanoTime();
		
		for (int i = 0; i < 1000; i++) {
			
			random243.find(find1000[i]);	
		}
		
		long time6 = System.nanoTime() - findTime6;
		
		System.out.println(time6 + "ns");
	}
}