#ifndef __MY_LIST_H
#define __MY_LIST_H

#include <stdio.h>
#include <malloc.h>

#include "bool.h"

typedef struct myList
{
  char* path;
  bool edited;
  struct myList *next;
} myList;

extern myList *open_list;

myList *new_list();
myList *new_node(char* path, int edited);
void add_node(myList *list, char* path, int edited);
myList *rm_node(myList *list, char* path);
bool contains_node(myList *list, char* path);
void set_edited(myList *list, char* path);
bool is_edited(myList *list, char* path);

#endif
