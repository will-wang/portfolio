/**
 * CS 2110 - Summer 2010 - Homework #9
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
	llist* list = (llist*)malloc(sizeof(llist));
	list->size = 0;
	list->head = create_node(NULL);
	return list;
}

/**
 * Creates a lnode
 *
 * void* data: data this node will contain.
 **/
lnode* create_node(void* data)
{
	/* FIX ME: Add your code here. */
	lnode *node = (lnode*)malloc(sizeof(lnode));
	node->prev = NULL;
	node->next = NULL;
	node->data = data;
	return node;
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
	if(list->head == NULL) {
		list->head = node;
		list->head->next = node;
		list->head->prev = node;
		list->size = ((list->size)+1);
	}
	else {
		node->next = list->head;
		node->prev = list->head->prev;
		list->head->prev->next = node;
		list->head->prev = node;
		list->head = node;
		list->size = ((list->size)+1);
	} 
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
	if(list->head == NULL) {
		list->head = node;
		list->head->next = node;
		list->head->prev = node;
		list->size = ((list->size)+1);
	}
	else {
		node->next = list->head;
		node->prev = list->head->prev;
		list->head->prev->next = node;
		list->head->prev = node;
		list->size = ((list->size)+1);
	}
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
	free_func = free_node;	
	if(list->head == NULL) {
		return -1;
	}
	else if(list->head->next == list->head) {
		free_func(list->head);
		list->head = NULL;
		list->size = ((list->size)-1);
	}
	else {
		lnode* temp = (lnode*)malloc(sizeof(lnode));
		temp = list->head->next;
		list->head->next->prev = list->head->prev;
		list->head->prev->next = list->head->next;
		free_func(list->head);
		list->head = temp;
		list->size = ((list->size)-1);
	}
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
	free_func = free_node;
	if(list->head == NULL) {
		return -1;
	}
	else if(list->head == list->head->next)
	{
		free_func(list->head);
		list->head = NULL;
		list->size = ((list->size)-1);
	}
	else {
		lnode* tail = (lnode*)malloc(sizeof(lnode));
		tail = list->head->prev;
		list->head->prev = tail->prev;
		tail->prev->next = list->head;
		free_func(tail);
		list->size = ((list->size)-1);
	}
 return 0;
}

/**
 * Searches for the first node in the forward direction with data equal to the
 *   data parameter.
 *
 * llist* list: a pointer to a linked list.
 * void* search: data to search for.
 * compare_op compare: comparision function used to compare two data items.
 *
 * Returns a pointer to the node if found, or NULL if not found.
 **/
lnode* find_occurrence(llist* list, void* search, compare_op compare)
{
 /* FIX ME: Add your code here. */
	compare = data_compare;
	if(list->head == NULL) {
		return NULL;
	}
	else {
		lnode* current = (lnode*)malloc(sizeof(lnode));
		current = list->head;
		do {
			if(compare(current->data, search) == 0) {
				return current;
			}
			current = current->next;
		} while(current != list->head);
	}
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
	free_func = free_node;
	if(list->head != NULL) {
		lnode* current = (lnode*)malloc(sizeof(current));
		current = list->head->prev;
		while(current != list->head) {
			lnode* temp = (lnode*)malloc(sizeof(temp));
			temp = current->prev;
			free_func(current);
			current = temp;
		}
		free_func(list->head);
		list->head = NULL;
		list->size = 0;
	}
}

/**
 * Traverses a linked list and calls do_func on each node.
 * llist* list: a pointer to a linked list.
 * list_op do_func: function pointer that should be called on each node.
 */
void traverse(llist* list, list_op do_func)
{
   /* FIX ME: Add your code here. */
	do_func = print_node;
	if(list->head == NULL) {
		printf("EMPTY LIST\n");
	}
	else {
		lnode *current = (lnode*)malloc(sizeof(lnode));
		current = list->head;
		do {
			do_func(current);
			current = current->next;
		} while(current != list->head);
	}
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
	if(node == NULL) {
		printf("print_node error: NULL node parameter\n");
	}
	else {
		printf("Data: %p\n", node->data);
	}
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
	node->data = NULL;
	node = NULL;
}

/**
  * Compares two node's data items
  * Returns a negative if a < b
  * Returns a positive if a > b
  * Returns zero if a == b
  * For this default implementation
  * just return a - b as an int
  */
int data_compare(const void* a, const void* b)
{
  /* FIXME: Add your code here */
	if(a == b) {
		return (0);
	}
	else if(a < b) {
		return (-1);
	}
	else {
		return 1;
	}
}
