#include "fs.h"
#include <stdlib.h>
#include <stdio.h>
/*
struct superblock
{
    int num_inodes; // number of inodes
    int num_blocks; // number of disk blocks
    int size_blocks; // size of the disk blocks
};


struct inode
{
    int size; // size of the file
    char name[8]; // name of the file
};

struct disk_block
{
    int next_block_num; // number of the next block
    char data[512]; // data of the block
};
*/

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
        inodes[i].name[0] = ""; // empty name
    }

    dbs = malloc(sizeof(struct disk_block) * sb.num_blocks);
    for (int i = 0; i < sb.num_blocks; i++){
        dbs[i].next_block_num = -1; // -1 means the block is free
    }
}

// load a filesystem
void mount_fs (); 

// write the filesystem
void sync_fs (){

}