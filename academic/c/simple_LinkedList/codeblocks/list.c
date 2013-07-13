/**
 * CS 2110 - Summer 2010 - Homework #12
 * Edited by: Brandon Whitehead
 *
 * list.c: Complete the functions!
 **/

#include <stdlib.h>
#include <stdio.h>
#include "list.h"

/**
 * Creates a llist
 *
 * Be sure to initialze size to zero
 * And head to NULL.
 **/
llist* create_list(void)
{
	/* FIX ME: Add your code here. */
	return NULL;
}

/**
 * Creates a lnode
 *
 * void* data: data this node will contain.
 **/
lnode* create_node(void* data)
{
	/* FIX ME: Add your code here. */
	return NULL;
}

/**
 * Adds a node to the front of a linked list.
 *
 * llist* list: a pointer to a linked list
 * lnode* node: a pointer to a linked list node to add
 **/
void add_front(llist* list, lnode* node)
{
 /* FIX ME: Add your code here. */
}

/**
 * Adds a node to the back of a linked list.
 *
 * llist* list: a pointer to a linked list
 * lnode* node: a pointer to a linked list node to add
 **/
void add_back(llist* list, lnode* node)
{
 /* FIX ME: Add your code here. */
}

/**
 * Removes a node from the front of a linked list.
 *   The removed node should be freed.
 *
 * llist* list: a pointer to a linked list.
 * list_op free_func: a function pointer to the node's free function.
 *
 * Returns 0 if the remove was successful, or -1 if empty list
 **/
int remove_front(llist* list, list_op free_func)
{
 /* FIX ME: Add your code here. */
 return 0;
}


/**
 * Removes a node from the back of a linked list.
 *   The removed node should be freed.
 *
 * llist* list: a pointer to a linked list.
 * list_op free_func: a function pointer to the node's free function.
 *
 * Returns 0 if the remove was successful, or -1 if empty list
 **/
int remove_back(llist* list, list_op free_func)
{
 /* FIX ME: Add your code here. */
 return 0;
}

/**
 * Searches for the first node in the forward direction with data equal to the
 *   data parameter.
 *
 * llist* list: a pointer to a linked list.
 * void* data: data to search for.
 * compare_op compare: comparision function used to compare two data items.
 *
 * Returns a pointer to the node if found, or NULL if not found.
 **/
lnode* find_occurrence(llist* list, void* search, compare_op compare)
{
 /* FIX ME: Add your code here. */
 return NULL;
}

/**
 * Frees an entire list.
 *
 * llist* list: a pointer to a linked list.
 * list_op free_func: function used to free a node
 *
 *  Do NOT free the list itself, only its nodes.
 **/
void free_list(llist* list, list_op free_func)
{
 /* FIX ME: Add your code here. */
}

/**
 * Traverses a linked list and calls do_func on each node.
 * llist* list: a pointer to a linked list.
 * list_op do_func: function pointer that should be called on each node.
 */
void traverse(llist* list, list_op do_func)
{
   /* FIX ME: Add your code here. */
}

/**
  * Prints the node's data.
  * For this default implementation 
  * Just call printf with the data
  * Use the %p for pointer for this.
  */
void print_node(lnode* node) 
{
  /* FIX ME: Add your code here. */
}

/**
  * Free's the node's data.
  * For this default implmentation
  * Just free the node's data.
  * And the node.
  */
void free_node(lnode* node)
{
	/* FIXME: Add your code here. */ 
}

/**
  * Compares two node's data items
  * Returns a negative if a < b
  * Returns a positive if a > b
  * Returns zero if a == b
  * For this default implementation
  * just return a - b
  */
int data_compare(const void* a, const void* b)
{
  /* FIXME: Add your code here */
}
