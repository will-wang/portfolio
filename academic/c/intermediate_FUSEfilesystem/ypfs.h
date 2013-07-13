#ifndef __YPFS_H
#define __YPFS_H

#define FUSE_USE_VERSION 26

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#ifdef linux
/* For pread()/pwrite() */
#define _XOPEN_SOURCE 500
#endif

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <errno.h>
#include <sys/time.h>

#include "util.h"


int ypfs_getattr(const char *path, struct stat *stbuf);
int ypfs_access(const char *path, int mask);
int ypfs_readlink(const char *path, char *buf, size_t size);
int ypfs_readdir(const char *path, void *buf, fuse_fill_dir_t filler,
			off_t offset, struct fuse_file_info *fi);
int ypfs_mknod(const char *path, mode_t mode, dev_t rdev);
int ypfs_mkdir(const char *path, mode_t mode);
int ypfs_unlink(const char *path);
int ypfs_rmdir(const char *path);
int ypfs_symlink(const char *from, const char *to);
int ypfs_rename(const char *from, const char *to);
int ypfs_link(const char *from, const char *to);
int ypfs_chmod(const char *path, mode_t mode);
int ypfs_chown(const char *path, uid_t uid, gid_t gid);
int ypfs_truncate(const char *path, off_t size);
int ypfs_utimens(const char *path, const struct timespec ts[2]);
int ypfs_open(const char *path, struct fuse_file_info *fi);
int ypfs_read(const char *path, char *buf, size_t size, off_t offset,
	      struct fuse_file_info *fi);
int ypfs_write(const char *path, const char *buf, size_t size,
	       off_t offset, struct fuse_file_info *fi);
int ypfs_release(const char *path, struct fuse_file_info *fi);
int ypfs_statfs(const char *path, struct statvfs *stbuf);

#endif
