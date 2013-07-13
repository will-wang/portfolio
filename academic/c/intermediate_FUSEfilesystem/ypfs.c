#include "ypfs.h"

int ypfs_getattr(const char *path, struct stat *stbuf)
{
  char* original_path = strdup(path);
  path = file_new_path(path);
  
  int res;
  
  res = lstat(path, stbuf);
  if (res == -1)
    {
      path = tmp_path(original_path);
      res = lstat(path, stbuf);
      if(res == -1)
	{
	  path = dir_new_path(original_path);
	  res = lstat(path, stbuf);
	  if(res == -1)
	    {
	      return -errno;
	    }
	}
    }
  return 0;
}

int ypfs_access(const char *path, int mask)
{
  int res;

  char* original_path = strdup(path);
  path = file_new_path(path);

  res = access(path, mask);
  if (res == -1)
    {
      path = tmp_path(original_path);
      res = access(path, mask);
      if(res == -1)
	{
	  path = dir_new_path(original_path);
	  res = access(path, mask);
	  if(res == -1)
	    {
	      return -errno;
	    }
	}
    }
  
  return 0;
}

int ypfs_readdir(const char *path, void *buf, fuse_fill_dir_t filler,
		 off_t offset, struct fuse_file_info *fi)
{
  DIR *dp;
  struct dirent *de;

  path = dir_new_path(path);

  (void) offset;
  (void) fi;

  dp = opendir(path);
  if (dp == NULL)
    return -errno;

  while ((de = readdir(dp)) != NULL) {
    struct stat st;
    memset(&st, 0, sizeof(st));
    st.st_ino = de->d_ino;
    st.st_mode = de->d_type << 12;
    if (filler(buf, de->d_name, &st, 0))
      break;
  }

  closedir(dp);
  return 0;
}

int ypfs_mknod(const char *path, mode_t mode, dev_t rdev)
{
  int res;

  path = tmp_path(path);

  res = mknod(path, mode, rdev);
  
  if (res == -1)
    return -errno;

  return 0;
}

int ypfs_rename(const char *from, const char *to)
{
  int res;

  from = file_new_path(from);
  to = file_new_path(to);

  res = rename(from, to);
  if (res == -1)
    return -errno;

  return 0;
}

int ypfs_chmod(const char *path, mode_t mode)
{
  int res;

  path = file_new_path(path);

  res = chmod(path, mode);
  if (res == -1)
    return -errno;

  return 0;
}

int ypfs_chown(const char *path, uid_t uid, gid_t gid)
{
  int res;

  path = file_new_path(path);

  res = lchown(path, uid, gid);
  if (res == -1)
    return -errno;

  return 0;
}

int ypfs_truncate(const char *path, off_t size)
{
  int res;

  char* original_path = strdup(path);
  path = file_new_path(path);

  res = truncate(path, size);
  if (res == -1)
    {
      path = tmp_path(original_path);
      res = truncate(path, size);
      if(res == -1)
	{
	  path = dir_new_path(original_path);
	  res = truncate(path, size);
	  if(res == -1)
	    {
	      return -errno;
	    }
	}
    }
  
  return 0;
}

int ypfs_utimens(const char *path, const struct timespec ts[2])
{
  int res;
  struct timeval tv[2];

  path = file_new_path(path);

  tv[0].tv_sec = ts[0].tv_sec;
  tv[0].tv_usec = ts[0].tv_nsec / 1000;
  tv[1].tv_sec = ts[1].tv_sec;
  tv[1].tv_usec = ts[1].tv_nsec / 1000;

  res = utimes(path, tv);
  if (res == -1)
    return -errno;

  return 0;
}

int ypfs_open(const char *path, struct fuse_file_info *fi)
{
  struct timeval start;
  struct timeval end;
  mark_time(&start);

  int res;

  char* original_path = strdup(path);
  
  /* Get the temp path */
  path = tmp_path(path);

  if(store_contains(original_path, false))
    {
      original_path = file_new_path(original_path);
      copy_file(original_path, path);
    }

  add_node(open_list, path, false);

  res = open(path, fi->flags);

  mark_time(&end);
  put_diff("/log/opentime.log", start, end);

  if (res == -1)
    return -errno;
  
  close(res);
  return 0;
}

int ypfs_read(const char *path, char *buf, size_t size, off_t offset,
	      struct fuse_file_info *fi)
{
  struct timeval start, end;
  mark_time(&start);

  path = tmp_path(path);
     
  int fd;
  int res;
  
  (void) fi;
  fd = open(path, O_RDONLY);
  if (fd == -1)
    return -errno;
  
  res = pread(fd, buf, size, offset);

  mark_time(&end);
  put_diff("/log/readtime.log", start, end);

  if (res == -1)
    res = -errno;
  
  close(fd);
  return res; 
}

int ypfs_write(const char *path, const char *buf, size_t size,
	       off_t offset, struct fuse_file_info *fi)
{
  struct timeval start, end;
  mark_time(&start);

  path = tmp_path(path);
  set_edited(open_list, path);

  int fd;
  int res;
  
  (void) fi;
  fd = open(path, O_WRONLY);
  if (fd == -1)
    return -errno;

  mark_time(&end);
  put_diff("/log/writetime.log", start, end);
  
  res = pwrite(fd, buf, size, offset);
  if (res == -1)
    res = -errno;
  
  close(fd);
  return res;
}

int ypfs_release(const char *path, struct fuse_file_info *fi)
{
  struct timeval start, end;
  mark_time(&start);

  path = tmp_path(path);

  if(is_edited(open_list, path))
    {
      move_back(path);
    }
  open_list = rm_node(open_list, path);

  mark_time(&end);
  put_diff("/log/releasetime.log", start, end);

  return 0;
}

int ypfs_statfs(const char *path, struct statvfs *stbuf)
{

  int res;

  path = file_new_path(path);

  res = statvfs(path, stbuf);
  if (res == -1)
    return -errno;

  return 0;
}
