#include "my_list.h"

myList *open_list;

myList *new_list()
{
  myList* newList = (myList*)malloc(sizeof(myList));
  newList->path = "";
  newList->edited = 0;
  newList->next = NULL;
  return newList;
}

myList *new_node(char* path, bool edited)
{
  myList* newNode = (myList*)malloc(sizeof(myList));
  newNode->path = path;
  newNode->edited = edited;
  newNode->next = NULL;
  return newNode;
}

void add_node(myList *list, char* path, bool edited)
{
  if(list->next == NULL)
    {
      myList* node = new_node(path, edited);
      list->next = node;
    }
  else
    {
      add_node(list->next, path, edited);
    }
}

myList *rm_node(myList *list, char* path)
{
  if(list == NULL)
    {
      return NULL;
    }
  else
    {
      if(strcmp(list->path, path) == 0)
	{
	  list = rm_node(list->next, path);
	  return list;
	}
      else
	{
	  list->next = rm_node(list->next, path);
	  return list;
	}
    }
}

bool contains_node(myList *list, char* path)
{
  if(list == NULL)
    {
      return false;
    }
  else
    {
      if(strcmp(list->path, path) == 0)
	{
	  return true;
	}
      else
	{
	  return contains_node(list, path);
	}
    }
}

void set_edited(myList *list, char* path)
{
  if(list == NULL)
    {
      return;
    }
  else
    {
      if(strcmp(list->path, path) == 0)
	{
	  list->edited = true;
	}
      set_edited(list->next, path);
    }
}

bool is_edited(myList *list, char* path)
{
  if(list == NULL)
    {
      return false;
    }
  else
    {
      if(strcmp(list->path, path) == 0)
	{
	  return list->edited;
	}
      else
	{
	  return is_edited(list->next, path);
	}
    }
}

void dump_list(myList *list, char* logfile)
{
  FILE *pFile = fopen(logfile, "a");
  
  fprintf(pFile, "Dumping List:\n");

  myList *traverse = list;
  while(traverse != NULL)
    {
      if(strcmp(traverse->path, ""))
	{
	  if(traverse->edited)
	    {
	      fprintf(pFile, "%s: Edited\n", traverse->path);
	    }
	  else
	    {
	      fprintf(pFile, "%s: Clean\n", traverse->path);
	    }
	}
      traverse = traverse->next;
    }

  fprintf(pFile, "Finished Dump\n");

  fclose(pFile);
}
