#ifndef __IMAGES_H
#define __IMAGES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wand/MagickWand.h>
#include <libexif/exif-data.h>

#include "bool.h"

char* get_date(const char* path);

int has_exif_data(const char* path);
struct tm* exif_date(const char* path);

char* get_current_date();

void convert(char* path, char* newPath);

#endif
