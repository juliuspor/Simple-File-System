#include "fs.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct superblock sb;
struct inode *inodes;
struct disk_block *dbs;

// create a new filesystem
void create_fs (){
    sb.num_inodes = 10;
    sb.num_blocks = 100;
    sb.size_blocks = sizeof(struct disk_block);

    inodes = malloc(sizeof(struct inode) * sb.num_inodes);
    for (int i = 0; i < sb.num_inodes; i++){
        inodes[i].size = -1; // -1 means the inode is free
        inodes[i].first_block = -1; // -1 means the inode is free
        strcpy(inodes[i].name, "emptyfil"); // empty name
    }

    dbs = malloc(sizeof(struct disk_block) * sb.num_blocks);
    for (int i = 0; i < sb.num_blocks; i++){
        dbs[i].next_block_num = -1; // -1 means the block is free
    }
}

// load a filesystem
void mount_fs (){
    FILE *file; 
    file = fopen("fs_data", "r");

    // write the superblock
    fread (&sb, sizeof(struct superblock), 1, file);

    // write the inodes
    for (int i = 0; i < sb.num_inodes; i++){
        fread (&inodes[i], sizeof(struct inode), 1, file);
    }
    
    // write the disk blocks
    for (int i = 0; i < sb.num_blocks; i++){
        fread (&dbs[i], sizeof(struct disk_block), 1, file);
    }

    fclose(file); 

}

// write the filesystem
void sync_fs (){
    FILE *file; 
    file = fopen("fs_data", "w+");

    // write the superblock
    fwrite (&sb, sizeof(struct superblock), 1, file);

    // write the inodes
    for (int i = 0; i < sb.num_inodes; i++){
        fwrite (&inodes[i], sizeof(struct inode), 1, file);
    }
    
    // write the disk blocks
    for (int i = 0; i < sb.num_blocks; i++){
        fwrite (&dbs[i], sizeof(struct disk_block), 1, file);
    }

    fclose(file); 
}

void print_fs(){
    printf("Superblock info:\n");
    printf("Number of inodes: %d\n", sb.num_inodes);
    printf("Number of blocks: %d\n", sb.num_blocks);
    printf("Size of blocks: %d\n", sb.size_blocks);
    printf("Inodes info:\n");
    for (int i = 0; i < sb.num_inodes; i++){
        printf("Inode %d: size = %d, name = %s\n", i, inodes[i].size, inodes[i].name);
    }
    printf("Disk blocks info:\n");
    for (int i = 0; i < sb.num_blocks; i++){
        printf("Block %d: next block = %d\n", i, dbs[i].next_block_num);
    }
}