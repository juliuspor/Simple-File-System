#include <stdio.h>
#include "fs.h"


void main(){

    // sync_fs();
    mount_fs();
    allocate_file("file1");
    sync_fs();
    print_fs();
    printf("Filesystem created and written to disk.\n");
}