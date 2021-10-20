#define FUSE_USE_VERSION 35

#include <iostream>
#include <fuse.h>

static void *xmp_init(struct fuse_conn_info *conn, struct fuse_config *cfg)
{
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

static int xmp_readdir(const char *path, void *buf, fuse_fill_dir_t filler, off_t offset, struct fuse_file_info *fi, enum fuse_readdir_flags flags)
{
    std::cout << "Looking in dir";
    return 0;
};

static const struct fuse_operations xmp_oper = {
    .readdir = xmp_readdir,
    .init = xmp_init,
};

int main(int argc, char *argv[])
{
    std::cout << "Hello world!\n";
    return fuse_main(argc, argv, &xmp_oper, NULL);
}
