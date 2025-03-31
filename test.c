#include <stdio.h>
#include "fs.h"


void main(){
    // create a new filesystem
    create_fs();

    // write the filesystem
    sync_fs();
    print_fs();
    printf("Filesystem created and written to disk.\n");
}