#include <stdio.h>
#include "fs.h"


void main(){
    mount_fs();
    int file = allocate_file("other");

    set_filesize(file, 5000);

    char data = 'b';

    for (int i = 0; i < 49; i++){
        write_byte(file, i*100, &data);
    }
    sync_fs();
    print_fs();
    printf("Filesystem created and written to disk.\n");
}