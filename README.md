# Simple File System Implementation

This project is a basic file system implementation from scratch.

## Features

- Works in memory but can be saved to disk
- Handles basic file operations (create and write)
- Simple flat file organization with named files

## How its organized
Three main components: 
- **Superblock**: Metadata about system
  - Number of inodes
  - Number of blocks
  - Size of blocks

- **Inodes**: File metadata
  - File size
  - First block pointer
  - File name (limited to 8 characters)

- **Blocks**: Store for actual file data
  - Fixed size (512 bytes)

## What you can do with it 

- `create_fs()`: Initialize a new empty file system
- `mount_fs()`: Load an existing file system from disk
- `sync_fs()`: Write the file system to disk
- `allocate_file()`: Create a new file with the given name
- `set_filesize()`: Adjust the size of a file (allocating or freeing blocks)
- `write_byte()`: Write data to a specific position in a file
- `print_fs()`: Display information about the file system