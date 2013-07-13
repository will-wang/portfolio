/* test.c
   Use this program to test your linked list library.
   It won't work unless you've implemented your print and traversal
   functions and create_node [marked TEST in list.c] ;)
*/

#include "list.h"
#include <stdlib.h>
#include <stdio.h>

/* Here we are going to write some functions to support a linked list that stores points (x, y) */
typedef struct point
{
	int x;
	int y;
} point;

point* create_point(int x, int y)
{
	/* TODO Implement */
}

void print_point_node(lnode* node)
{
	/* TODO Implement */
}

void free_point_node(lnode* node)
{
	/* TODO Implement */
}

int compare_point_data(const void* a, const void* b)
{
	/* TODO Implement compare by x then y here*/
}

/* This main function does a little testing
   Like all good CS Majors you are required to test
   your code here. There is no substitute for testing
   and you should be sure to test for all edge cases
   ex. calling remove_front on an empty list.
*/
int main(void) 
{
	/* Now to make use of all of this stuff */
  llist* list = create_list();
  
  /* What does an empty list contain?  Lets use our handy traversal function */
  printf("TEST CASE 1\nAn Empty list should print nothing here:");
  traverse(list, print_point_node);
	printf("\n");

 	/* Lets add a point and then print */
 	add_front(list, create_node(create_point(3, 5)));
 	printf("TEST CASE 2\nA List with (3, 5) should print (3, 5):");
 	traverse(list, print_point_node);
 	printf("\n");
 	
 	/* Lets remove a point and then print */
 	remove_front(list);
 	printf("TEST CASE 3\nAnother Empty list should print nothing here:");
 	traverse(list, print_point_node);
 	printf("\n");

 	/* Lets add two points and then print */
 	add_front(list, create_node(create_point(3, 5), create_point(9, 16)));
 	printf("TEST CASE 4\nA List with two nodes should print those two nodes:");
 	traverse(list, print_point_node);
 	printf("\n"); 	
 	
  /* Lets kill the list */
  free_list(list, free_point_node);
 	printf("TEST CASE 5\nAfter freeing all nodes the list should be empty:");
 	traverse(list, print_point_node);
 	printf("\n"); 	
 	
 	/* YOU ARE REQUIRED TO MAKE MORE TEST CASES THAN THE ONES PROVIDED HERE */
 	
 	
 	/* Testing over clean up*/
 	free(list);
 	
  return 0;
}
