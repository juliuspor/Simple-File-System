// meta information about the filesystem
// number of inodes
// number of disk blocks
// size of the disk blocks
struct superblock
{
    int num_inodes; // number of inodes
    int num_blocks; // number of disk blocks
    int size_blocks; // size of the disk blocks
};


struct inode
{
    int size; // size of the file
    int first_block; // number of the first block
    char name[8]; // name of the file
};

struct disk_block
{
    int next_block_num; // number of the next block
    char data[512]; // data of the block
};

void create_fs (); // create a new filesystem
void mount_fs ();  // load a filesystem
void sync_fs ();   // write the filesystem


int allocate_file(char name[8]); // allocate a file and return filenumber


void print_fs (); // print info about the filesystem