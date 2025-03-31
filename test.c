#include <stdio.h>
#include "fs.h"


void main(){
    mount_fs();

    set_filesize(0, 5000);

    char data = 'a';

    for (int i = 0; i < 49; i++){
        write_byte(0, i*100, &data);
    }
    sync_fs();
    print_fs();
    printf("Filesystem created and written to disk.\n");
}