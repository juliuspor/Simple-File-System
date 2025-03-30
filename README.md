# Simple File System Implementation

This project is a basic file system implementation from scratch.

## File System Structure

The file system is organized as follows:

- **Superblock**:
  - Write: Handles writing metadata to the superblock.
  - Read: Handles reading metadata from the superblock.
- **Inode**:
  - Write: Manages writing inode information.
  - Read: Manages reading inode information.
- **Block**:
  - Write: Handles writing data blocks.
  - Read: Handles reading data blocks.
- **File**:
  - Write: Manages writing file data.
  - Read: Manages reading file data.

## Getting Started

1. Clone this repository.
2. Compile the code using a C compiler (e.g., `gcc`).
3. Run the program to explore the file system functionalities.