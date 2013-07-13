#include "main.h"

static struct fuse_operations ypfs_oper = {
	.getattr	= ypfs_getattr,
	.access		= ypfs_access,
	.readdir	= ypfs_readdir,
	.mknod		= ypfs_mknod,
	.rename		= ypfs_rename,
	.chmod		= ypfs_chmod,
	.chown		= ypfs_chown,
	.truncate	= ypfs_truncate,
	.utimens	= ypfs_utimens,
	.open		= ypfs_open,
	.read		= ypfs_read,
	.write		= ypfs_write,
	.release	= ypfs_release,
	.statfs		= ypfs_statfs,
};

int main(int argc, char *argv[])
{
	umask(0);
	
	char * home = getenv("HOME");
	printf("Home: %s\n", home);
	set_store_location(home);
	printf("store location: %s\n", storeLocation);
	open_list = new_list();
	return fuse_main(argc, argv, &ypfs_oper, NULL);
}