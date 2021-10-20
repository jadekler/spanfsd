#define FUSE_USE_VERSION 35

#include <stdio.h>
#include <errno.h>
#include <sys/xattr.h>

#include <fuse.h>

static void *xmp_init(struct fuse_conn_info *conn, struct fuse_config *cfg)
{
    printf("++++++++++++++++++ xmp_init\n");
    (void)conn;
    cfg->use_ino = 1;

    /* Pick up changes from lower filesystem right away. This is
	   also necessary for better hardlink support. When the kernel
	   calls the unlink() handler, it does not know the inode of
	   the to-be-removed entry and can therefore not invalidate
	   the cache of the associated inode - resulting in an
	   incorrect st_nlink value being reported for any remaining
	   hardlinks to this inode. */
    cfg->entry_timeout = 0;
    cfg->attr_timeout = 0;
    cfg->negative_timeout = 0;

    return NULL;
};

static int xmp_getattr(const char *path, struct stat *stbuf, struct fuse_file_info *fi)
{
    printf("++++++++++++++++++ xmp_getattr %s\n", path);

    int res = lstat(path, stbuf);
    if (res == -1)
        return -errno;

    return 0;
};

static int xmp_getxattr(const char *path, const char *name, char *value, size_t size)
{
    printf("++++++++++++++++++ xmp_getxattr path=%s, name=%s, value=%s\n", path, name, value);

    int res = lgetxattr(path, name, value, size);
    if (res == -1)
        return -errno;
    return res;

    return 0;
};

static int xmp_access(const char *path, int mask)
{
    printf("++++++++++++++++++ xmp_access %s\n", path);
    return 0;
};

static int xmp_readdir(const char *path, void *buf, fuse_fill_dir_t filler, off_t offset, struct fuse_file_info *fi, enum fuse_readdir_flags flags)
{
    printf("++++++++++++++++++ xmp_readdir %s\n", path);
    return 0;
};

static const struct fuse_operations xmp_oper = {
    .getattr = xmp_getattr,
    .getxattr = xmp_getxattr,
    .readdir = xmp_readdir,
    .init = xmp_init,
    .access = xmp_access,
};

int main(int argc, char *argv[])
{
    printf("++++++++++++++++++ main\n");
    return fuse_main(argc, argv, &xmp_oper, NULL);
}
