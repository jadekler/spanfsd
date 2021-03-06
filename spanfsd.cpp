#define FUSE_USE_VERSION 35

#include <string>
#include <cstdint>
#include <cstring>
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
    (void)fi;
    printf("++++++++++++++++++ xmp_getattr %s\n", path);

    std::string pathStr(path);
    if (pathStr == "/")
    {
        stbuf->st_mode = S_IFDIR | 0755;
        stbuf->st_nlink = 2;
    }
    else if (pathStr == "/foo")
    {
        printf("++++++++++++++++++ made up results! %s\n", path);
        stbuf->st_mode = S_IFREG | 0444;
        stbuf->st_nlink = 1;
        stbuf->st_size = strlen("hello world");
    }
    else
        return -ENOENT;

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
    
    int res = filler(buf, "foo", NULL, 0, FUSE_FILL_DIR_PLUS);

    printf("++++++++++++++++++ filler result=%d\n", res);

    return 0;
};

static int xmp_open(const char *path, struct fuse_file_info *fi)
{
    printf("++++++++++++++++++ xmp_open %s\n", path);
    return 0;
}

static int xmp_read(const char *path, char *buf, size_t size, off_t offset, struct fuse_file_info *fi)
{
    printf("++++++++++++++++++ xmp_read path=%s,size=%ld,offset=%ld\n", path, size, offset);
    char* str = "hello world";

    size_t len = strlen(str);
    if (offset < len)
    {
        if (offset + size > len)
            size = len - offset;
        memcpy(buf, str + offset, size);
    }
    else
        size = 0;

    return size;
};

static const struct fuse_operations xmp_oper = {
    .getattr = xmp_getattr,
    .open = xmp_open,
    .read = xmp_read,
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
