#include "fs.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct superblock sb;
struct inode *inodes;
struct disk_block *dbs;

int find_empty_inode(){
    for (int i = 0; i < sb.num_inodes; i++){
        if (inodes[i].first_block == -1){
            return i;
        }
    }
    return -1; 
}

int find_empty_block(){
    for (int i = 0; i < sb.num_blocks; i++){
        if (dbs[i].next_block_num == -1){
            return i;
        }
    }
    return -1; 
}

void shorten_file(int bn){
    int nn = dbs[bn].next_block_num;
    if (dbs[bn].next_block_num >= 0){
        shorten_file(nn);
    }
    dbs[bn].next_block_num = -1; // free the block
}


int get_block_num(int file, int offset){
    int togo = offset;
    int bn = inodes[file].first_block;

    while (togo > 0){
        bn = dbs[bn].next_block_num;
        togo--;
    }
    return bn;
}

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

    inodes = malloc(sizeof(struct inode) * sb.num_inodes);
    dbs = malloc(sizeof(struct disk_block) * sb.num_blocks);

    fread( inodes, sizeof(struct inode), sb.num_inodes, file);
    fread( dbs, sizeof(struct disk_block), sb.num_blocks, file);

    fclose(file); 
}

// write the filesystem
void sync_fs (){
    FILE *file; 
    file = fopen("fs_data", "w+");

    // write the superblock
    fwrite (&sb, sizeof(struct superblock), 1, file);

    // write the inodes and dbs
    fwrite( inodes, sizeof(struct inode), sb.num_inodes, file);
    fwrite( dbs, sizeof(struct disk_block), sb.num_blocks, file);

    fclose(file); 
}

int allocate_file(char name[8]){
    int inode = find_empty_inode();
    int block = find_empty_block();

    inodes[inode].first_block = block; 
    dbs[block].next_block_num = -2; 

    strcpy(inodes[inode].name, name);

    return inode; 
}

void set_filesize(int filenum, int size){
    int tmp = size + BLOCKSIZE - 1; 
    int num = tmp / BLOCKSIZE; 

    int bn = inodes[filenum].first_block; 
    bn--; 
    // grow the file if necessary 
    while (num > 0){
        int next_num = dbs[bn].next_block_num;
        if (next_num == -2){
            int empty = find_empty_block();
            dbs[bn].next_block_num = empty;
            dbs[empty].next_block_num = -2;
        }
        bn = dbs[bn].next_block_num;
        num--; 
    }

    // shorten if necessary 
    shorten_file(bn);
    dbs[bn].next_block_num = -2; // free the block
} 

void write_byte (int filenum, int pos, char *data){
    // calculate which block to write 
    int relative_block = pos / BLOCKSIZE;

    // find the block number 
    int bn = get_block_num(filenum, relative_block);

    // find the offset in the block
    int offset = pos % BLOCKSIZE;

    // write the data to the block
    dbs[bn].data[offset] = *data;
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