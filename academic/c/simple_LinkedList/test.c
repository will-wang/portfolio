/* test.c
   Use this program to test your linked list library.
   It won't work unless you've implemented your print and traversal
   functions [marked TEST in list.c] ;)
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
	point* pointy = (point*)malloc(sizeof(point));
	pointy->x = x;
	pointy->y = y;	
	return pointy;
}

void print_point_node(lnode* node)
{
}

void free_point_node(lnode* node)
{
}

/* The const void*'s here are of type point* */
int compare_point_data(const void* a, const void* b)
{
	return 0xCAFEBABE;
}

/* This main function does a little testing
   Like all good CS Majors you are required to test
   your code here. There is no substitute for testing
   and you should be sure to test for all edge cases
   ex. calling remove_front on an empty list.
*/


int main(void) {
  llist* list = create_list();
  lnode* new_node;
  lnode* found_node;
  point* p = create_point(0, 0);
  list->head = NULL;

  /* test case 1 - what does an empty list contain? */
  printf("TEST CASE 1\n");
  traverse(list, print_point_node);
  printf("\n");

  /* test case 2 - what happens when you add a node to the
     front of an empty list? */
  printf("TEST CASE 2\n");
  new_node = create_node(create_point(2,5));
  add_front(list, new_node);
  traverse(list, print_point_node);
  printf("\n");

  /* test case 3 - what happens when you add a node to the front
     of a list with one node? */
  printf("TEST CASE 3\n");
  new_node = create_node(create_point(3,7));
  add_front(list, new_node);
  traverse(list, print_point_node);
  printf("\n");

  /* test case 4 - what happens when you add a node to the front
     of a list with more than one node? */
  printf("TEST CASE 4\n");
  new_node = create_node(create_point(1,4));
  add_front(list, new_node);
  traverse(list, print_point_node);
  printf("\n");

  /* test case 5 - what happens when you remove a node from the front
     of a list with more than one node? */
  printf("TEST CASE 5\n");
  remove_front(list, free_point_node);
  traverse(list, print_point_node);
  printf("\n");

  /* test case 6 - what happens when you remove a node from the front
     of a list with one node? */
  printf("TEST CASE 6\n");
  remove_front(list, free_point_node);
  traverse(list, print_point_node);
  printf("\n");

  /* test case 7 - what happens when you remove a node from the front
     of an empty list? */
  printf("TEST CASE 7\n");
  remove_front(list, free_point_node);
  traverse(list, print_point_node);
  printf("\n");

  /* test case 8 - what happens when you add a node to the
     back of an empty list? */
  printf("TEST CASE 8\n");
  new_node = create_node(create_point(2,5));
  add_back(list, new_node);
  traverse(list, print_point_node);
  printf("\n");

  /* test case 9 - what happens when you add a node to the back
     of a list with one node? */
  printf("TEST CASE 9\n");
  new_node = create_node(create_point(3,7));
  add_back(list, new_node);
  traverse(list, print_point_node);
  printf("\n");

  /* test case 10 - what happens when you add a node to the back
     of a list with more than one node? */
  printf("TEST CASE 10\n");
  new_node = create_node(create_point(1,4));
  add_back(list, new_node);
  traverse(list, print_point_node);
  printf("\n");

  /* test case 11 - what happens when you remove a node from the back
     of a list with more than one node? */
  printf("TEST CASE 11\n");
  remove_back(list, free_point_node);
  traverse(list, print_point_node);
  printf("\n");

  /* test case 12 - what happens when you remove a node from the back
     of a list with one node? */
  printf("TEST CASE 12\n");
  remove_back(list, free_point_node);
  traverse(list, print_point_node);
  printf("\n");

  /* test case 13 - what happens when you remove a node from the back
     of an empty list? */
  printf("TEST CASE 13\n");
  remove_back(list, free_point_node);
  traverse(list, print_point_node);
  printf("\n");

  /* test case 14 - what happens when you try to find an occurrence
     of a given data point in an empty list? */
  printf("TEST CASE 14\n");
  p->x = 3;
  p->y = 7;
  found_node = find_occurrence(list, p, compare_point_data);
  print_point_node(found_node);
  printf("\n");

  /* test case 15 - what happens when you try to find an occurrence
     of a given data point in a list of that one node? */
  printf("TEST CASE 15\n");
  p->x = 3;
  p->y = 7;
  new_node = create_node(create_point(3, 7));
  add_front(list, new_node);
  found_node = find_occurrence(list, p, compare_point_data);
  print_point_node(found_node);
  printf("\n");
  
  /* test case 16 - what happens when you try to find an occurrence
     of a given data point in a list of one different node? */
  printf("TEST CASE 16\n");
  p->x = 5;
  p->y = 14;
  found_node = find_occurrence(list, p, compare_point_data);
  print_point_node(found_node);
  printf("\n");

  /* test case 17 - what happens when you try to find an occurrence
     of a given data point in a list of lots of nodes (one matching)?
     NOTE: if your list contains multiple nodes with matching data,
     returning any of them is fine.
  */
  printf("TEST CASE 17\n");
  new_node = create_node(create_point(5,2));
  add_front(list, new_node);
  new_node = create_node(create_point(6,30));
  add_back(list, new_node);
  new_node = create_node(create_point(1,1));
  add_front(list, new_node);
  p->x = 3;
  p->y = 7;
  found_node = find_occurrence(list, p, compare_point_data);
  print_point_node(found_node);
  printf("\n");

  /* test case 18 - what happens when you try to find an occurrence
     of a given data point in a list of lots of nodes (none matching)? */
  printf("TEST CASE 18\n");
  p->x = 5;
  p->y = 14;
  found_node = find_occurrence(list, p, compare_point_data);
  print_point_node(found_node);
  printf("\n");

  /* test case 19 - what happens when you try to free a list
     of lots of nodes? YOU WILL HAVE TO RUN VALGRIND TO MAKE
     SURE YOU GET NO ERRORS HERE. Memory leaks are otherwise
     invisible!
  */
  printf("TEST CASE 19\n");
  free_list(list, free_point_node);
  traverse(list, print_point_node);
  printf("\n");

  /* test case 20 - what happens when you try to free a list
     of one node? YOU WILL HAVE TO RUN VALGRIND TO MAKE
     SURE YOU GET NO ERRORS HERE. 
  */
  printf("TEST CASE 20\n");
  new_node = create_node(create_point(7,14));
  add_front(list, new_node);
  free_list(list, free_point_node);
  traverse(list, print_point_node);
  printf("\n");

  /* test case 21 - what happens when you try to free an empty list?
     YOU WILL HAVE TO RUN VALGRIND TO MAKE SURE YOU GET NO ERRORS HERE.
  */
  printf("TEST CASE 21\n");
  free_list(list, free_point_node);
  traverse(list, print_point_node);
  printf("\n");
  

	free(p);
  free(list);
  return 0;
}


