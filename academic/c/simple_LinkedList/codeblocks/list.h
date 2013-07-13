/**
 * CS 2110 - Spring 2010 - Homework #12
 * Edited by: Brandon Whitehead
 *
 * list.h: Fix the datatype definitions!
 **/

#ifndef _LIST_H_DEF_
#define _LIST_H_DEF_


/*************************
** Datatype definitions **
**************************/

/* The node struct.  Has a prev pointer, next pointer, and data. */
/* NOTE PLEASE DEFINE THE FIELDS IN THE ORDER GIVEN! */
typedef struct
{
  /* FIXME: Declare a prev pointer named 'prev' here. */
  /* FIXME: Declare a next pointer named 'next' here. */
  /* FIXME: Declare an void pointer named 'data' here. */
} lnode;

/* The linked list struct.  Has a head pointer. */
typedef struct
{
 /* FIXME: Declare a head pointer named 'head' here. */
 /* FIXME: Declare an unsigned integer named 'size' here. */
} llist;

/* FIXME Typedef a new function pointer type that points to a function that takes in an lnode* and returns nothing call it list_op */
/* FIXME Typedef a new function pointer type that points to a function that takes in 2 const void*'s and returns an int call it compare_op */
/**************************************************
** Prototypes for linked list library functions. **
**                                               **
** For more details on their functionality,      **
** check list.c.                                 **
***************************************************/

/* Creating */
llist* create_list(void);
lnode* create_node(void* data);

/* Adding */
void add_front(llist* list, lnode* node);
void add_back(llist* list, lnode* node);

/* Removing */
int remove_front(llist* list, list_op free_func);
int remove_back(llist* list, list_op free_func);

/* Searching */
lnode* find_occurrence(llist* list, void* search, compare_op compare);

/* Freeing */
void free_list(llist* list, list_op free_func);
void free_node(lnode* node);

/* Traversal */
void traverse(llist* list, list_op do_func);

/* Printing */
void print_node(lnode* node);

/* Comparision */
int data_compare(const void* a, const void* b);

/* Debugging Support */
#ifdef DEBUG
		/* 
			Does the following if compiled in debug mode 
			When compiled in release mode does absolutely nothing.
		*/
    #define IF_DEBUG(call) (call)
    /* Prints text (in red) if in debug mode */
    #define DEBUG_PRINT(string) fprintf(stderr, "\033[31m%s:%d %s\n\033[0m", __FILE__, __LINE__, (string))
    /* Asserts if the expression given is true (!0) */
    /* If this fails it prints a message and terminates */
    #define DEBUG_ASSERT(expr)   \
    do												   \
    {													   \
    	if (!(expr))               \
    	{												   \
    		fprintf(stderr, "ASSERTION FAILED %s != TRUE (%d) IN %s ON line %d\n", #expr, (expr), __FILE__, __LINE__); \
    		exit(0);							   \
    	}                          \
    } while(0)
    		
#else
    #define IF_DEBUG(call) 
    #define DEBUG_PRINT(string)
    #define DEBUG_ASSERT(expr)  
#endif

#endif
