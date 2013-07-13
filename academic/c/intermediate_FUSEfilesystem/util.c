#include "util.h"

char* storeLocation;
int storeLocationLength;

bool ends_with(const char* str, const char* ending);
bool is_image(char* path);

char* date_path();
void make_date_path();

void add_directory(char* path);

char* prefix_path(char* prefix, char* path);

char* get_filename(char* path);

/*
 * sets the location of the store
 * and the temp directory based on the location of our filesystem.
 */
void set_store_location(char* loc)
{
  storeLocation = prefix_path(loc, STORE_NAME);
  add_directory(TEMP_NAME);
}

/*
 * Determine whetehr "str" ends in "ending"
 */
bool ends_with(const char* str, const char* ending)
{
  int str_length = strlen(str);
  int ending_length = strlen(ending);

  if(ending_length > str_length)
    {
      /* That's just not gonna work */
      return false;
    }

  const char* str_end = &str[str_length-ending_length];
  return (strcmp(str_end, ending) == 0);
}

/*
 *
 */
bool is_image(char* path)
{
  return (ends_with(path, ".png") ||
	  ends_with(path, ".jpg") ||
	  ends_with(path, ".jpeg") ||
	  ends_with(path, ".gif"));
}

/*
 * prefix the "path" argument with the "prefix" argument.
 */
char* prefix_path(char* prefix, char* path)
{
  int pathLength = strlen(path);
  int prefixLength = strlen(prefix);

  int length = prefixLength+pathLength+2; // not sure why the +2
  char* prefixedPath = (char*)malloc(length*sizeof(char));

  sprintf(prefixedPath, "%s%s\0", prefix, path);

  return prefixedPath;
}

/*
 * get the filename at teh end of a path
 */
char* get_filename(char* path)
{
  char* ptr = strrchr(path, '/');
  if(ptr != NULL)
    {
      return ptr;
    }
  else
    {
      return path;
    }
}

/*
 * Does the store contain this path?
 */
bool store_contains(const char * path, bool check_tmp)
{
  char* storePath = prefix_path(storeLocation, path);
  char* tmpPath = tmp_path(path);
  
  struct stat st;
  if(lstat(storePath, &st) == 0)
    {
      return true;
    }
  else if(check_tmp && lstat(tmpPath, &st) == 0)
    {
      return true;
    }
  else
    {
      return false;
    }
}

/*
 * Determines whether a file should be in the store
 * or in the main fs.
 * Returns the global path either way.
 */
char* file_new_path(const char* path)
{
  char* workingPath = strdup(path);
  char* datePath = date_path();
  
  if(store_contains(workingPath, false))
    {
      workingPath = prefix_path(storeLocation,workingPath);
    }
  
  return workingPath;
}

/*
 * Determines whether a directory should be in the store
 * or in the main fs.
 * Returns the global path either way.
 */
char* dir_new_path(const char* path)
{
  int pathLength = strlen(path);
  char* workingPath = strdup(path);

  if(store_contains(workingPath, false))
    {
      workingPath = prefix_path(storeLocation, workingPath);
    }
  
  return workingPath;
}

/*
 * Make the given date into a path
 */
char* date_path(int year, int month, int day)
{
  char *path = (char*) malloc(12*sizeof(char));
  sprintf(path, "/%d/%d/%d", year, month, day);
  return path;
}

/*
 * Make the given date in the store
 */
void make_date_path(int year, int month, int day)
{
  char* path;

  /* Make Year Directory */
  char year_str[5];
  sprintf(year_str, "/%d/", year);
  path = year_str;
  if(!store_contains(path, false))
    {
      add_directory(path);
    }
  
  /* Make Month Directory*/
  char month_str[3];
  sprintf(month_str, "%d/", month);
  path = prefix_path(path, month_str);
  if(!store_contains(path, false))
    {
      add_directory(path);
    }

  /* Make Date Directory */
  char day_str[3];
  sprintf(day_str, "%d/", day);
  path = prefix_path(path, day_str);
  if(!store_contains(path, false))
    {
      add_directory(path);
    }
}


/*
 * Add a directory to the store
 */
void add_directory(char* local_path)
{
  char* path = prefix_path(storeLocation, local_path);
  int ret = mkdir(path, S_IRWXU | S_IRWXG | S_IRWXO);
}

/*
 * Prefix this file with the temp directory path
 */
char* tmp_path(const char* path)
{
  char* filename = get_filename(path);
  return prefix_path(storeLocation, prefix_path(TEMP_NAME, filename));
}

/*
 * Does this path start in the temp directory?
 */
bool is_tmp_path(const char* path)
{
  char* prefix = prefix_path(storeLocation, TEMP_NAME);
  int length = strlen(prefix);
  return (strncmp(prefix, path, length) == 0);
}

/*
 * Totally non-descript name for changing from the temp filename to the date filename
 */
char* fix_tmp_path(const char* path)
{
  char* tmp_prefix = prefix_path(storeLocation, TEMP_NAME);
  int length = strlen(tmp_prefix);
  char* ending = &path[length];
  
  char* new_prefix;

  struct tm *time_info;
  
  if(has_exif_data(path))
    {
      time_info = exif_date(path);
    }
  else
    {
      time_t raw_time;
      time(&raw_time);
      time_info = localtime(&raw_time);
    }

  new_prefix = prefix_path(storeLocation, 
			   date_path(time_info->tm_year+1900, 
				     time_info->tm_mon+1, 
				     time_info->tm_mday));
  
  
  char* new_path = prefix_path(new_prefix, ending);
  make_date_path(time_info->tm_year+1900,
		 time_info->tm_mon+1,
		 time_info->tm_mday);
  
  return new_path;
}

/*
 * File operations
 */
void copy_file(char *src, char* dest)
{
  FILE *source = fopen(src, "rb");
  FILE *destination = fopen(dest, "wb");


  if(source == NULL ||
     destination == NULL)
    {
      return;
    }
  
  fseek (source , 0 , SEEK_END);
  int bytes = ftell (source);
  rewind (source);
  
  char* buffer = (char*)malloc(bytes*sizeof(char));
  
  fread(buffer, sizeof(char), bytes, source);
  fwrite(buffer, sizeof(char), bytes, destination);
  
  fclose(source);
  fclose(destination);
}

void delete_file(char *path)
{
  remove(path);
}

void move_file(char *from, char* to)
{
  copy_file(from, to);
  remove(from);
}

void move_back(char *path)
{
  char* newPath = fix_tmp_path(path);

  bool isImage = is_image(path);

  if(isImage)
    {
      convert(path, newPath);
    }
  else
    {
      rename(path, newPath);
    }
}

void mark_time(struct timeval *time)
{
  gettimeofday(time, NULL);
}

void put_diff(const char* filename, struct timeval start, struct timeval end)
{
  FILE *pFile = fopen(filename, "a");
  long diff_sec = end.tv_sec-start.tv_sec;
  long diff_usec = end.tv_usec-start.tv_usec;
  double diff_time = diff_sec + (((double)diff_usec)/1000000.0);

  fprintf(pFile, "%f\n", diff_time);
  
  fclose(pFile);
}
