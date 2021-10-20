#define FUSE_USE_VERSION 35

#include <iostream>
#include <fuse.h>

static const struct fuse_operations xmp_oper = {
};

int main(int argc, char *argv[]) {
    std::cout << "Hello world!\n";

    return fuse_main(argc, argv, &xmp_oper, NULL);
}
