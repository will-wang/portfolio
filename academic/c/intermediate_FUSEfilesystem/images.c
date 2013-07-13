#include "images.h"

void postfix_types(char* path, char* jpg, char* gif, char* png);

static void trim_spaces(char *buf)
{
  char *s = buf-1;
  for (; *buf; ++buf) 
    {
      if (*buf != ' ')
	s = buf;
    }
  *++s = 0; /* nul terminate the string on the first of the final spaces */
}

int has_exif_data(const char* path)
{
  ExifData *ed;
  ExifEntry *entry;
  
  ed = exif_data_new_from_file(path);

  if(!ed)
    {
      return false;
    }

  /* See if this tag exists */
  ExifIfd ifd = EXIF_IFD_EXIF;
  ExifTag tag = EXIF_TAG_DATE_TIME_ORIGINAL;  
  
  entry = exif_content_get_entry(ed->ifd[ifd],tag);
  if (entry) 
    {
      char buf[1024];
      
      /* Get the contents of the tag in human-readable form */
      exif_entry_get_value(entry, buf, sizeof(buf));
      
      /* Don't bother printing it if it's entirely blank */
      trim_spaces(buf);
      if (*buf)
	{
	  exif_data_unref(ed);
	  return true;
	}
    }
  
  exif_data_unref(ed);

  return false;
}

struct tm *exif_date(const char* path)
{
  struct tm *time_info = (struct tm*)malloc(sizeof(struct tm));
  
  time_info->tm_year = 0;
  time_info->tm_mon = 0;
  time_info->tm_mday = 0;

  ExifData *ed;
  ExifEntry *entry;
  
  ed = exif_data_new_from_file(path);

  if(!ed)
    {
      return false;
    }

  /* See if this tag exists */
  ExifIfd ifd = EXIF_IFD_EXIF;
  ExifTag tag = EXIF_TAG_DATE_TIME_ORIGINAL;  
  
  entry = exif_content_get_entry(ed->ifd[ifd],tag);
  if (entry) 
    {
      char buf[1024];
      
      /* Get the contents of the tag in human-readable form */
      exif_entry_get_value(entry, buf, sizeof(buf));
      
      /* Don't bother printing it if it's entirely blank */
      trim_spaces(buf);
      if (*buf)
	{
	  int year, month, day;
	  sscanf(buf, "%d:%d:%d", &year, &month, &day);

	  time_info->tm_year = year-1900;
	  time_info->tm_mon = month-1;
	  time_info->tm_mday = day;
	}
    }
  
  exif_data_unref(ed);

  return time_info;
}

void replace_ending(char *str, char *ending, int end_size)
{
  static char buffer[4096];
  char* p;

  if(!(p = strrchr(str, '.')))
    return;

  int q = p-str;

  int i = 0;
  for(i = 0; i < end_size; i++)
    {
      str[q+i] = ending[i];
    }
}

void convert(char* path, char* newPath)
{
  char* jpg_path;
  char* gif_path;
  char* png_path;

  jpg_path = strdup(newPath);
  gif_path = strdup(newPath);
  png_path = strdup(newPath);

  replace_ending(jpg_path, ".jpg", 4);
  replace_ending(gif_path, ".gif", 4);
  replace_ending(png_path, ".png", 4);
  
  MagickBooleanType status;  

  MagickWandGenesis();
  
  MagickWand *magick_wand = NewMagickWand();

  status = MagickReadImage(magick_wand, path);

  status = MagickWriteImage(magick_wand, jpg_path);
  status = MagickWriteImage(magick_wand, gif_path);
  status = MagickWriteImage(magick_wand, png_path);

  if(magick_wand)
    {
      DestroyMagickWand(magick_wand);
    }

  MagickWandTerminus();

}
