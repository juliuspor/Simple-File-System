#include <stdio.h>
#include "fs.h"


void main(){
    // create a new filesystem
    create_fs();
    sync_fs();
    mount_fs();
    print_fs();
    printf("Filesystem created and written to disk.\n");
}