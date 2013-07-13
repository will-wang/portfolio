#ifndef __UTIL_H
#define __UTIL_H

#include <fuse.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>

#include "bool.h"
#include "my_list.h"
#include "images.h"

#define STORE_NAME ("/.ypfsStore")
#define TEMP_NAME ("/.ypfsTemp")

extern char* storeLocation;

void set_store_location(char* mount);
bool store_contains(const char* path, bool check_tmp);

char* file_new_path(const char* path);
char* dir_new_path(const char* path);
char* tmp_path(const char* path);
bool is_tmp_path(const char* path);
char* fix_tmp_path(const char* path);

void print_log(char* msg);

/*
 * File Operations
 */
void copy_file(char *src, char* dest);
void delete_file(char *path);
void move_file(char *from, char* to);


/*
 * Log Operations
 */
void mark_time(struct timeval *time);
void put_diff(const char* filename, struct timeval start, struct timeval end);

#endif
