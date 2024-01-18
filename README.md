#  B-Tree-Indexing Project

## Overview

This project implements a B-Tree indexing system in C++. The B-Tree is a self-balancing tree data structure that maintains sorted data and allows for efficient insertion, deletion, and search operations.

## Why B-Tree-Indexing in File Management?
B-Tree indexing is widely used in file management systems because it provides efficient searching and retrieval of records from large datasets. The self-balancing nature of B-Trees ensures that the tree remains balanced, leading to predictable and fast search times. This makes B-Tree indexing suitable for applications where data needs to be organized and accessed quickly, such as file systems, databases, and filesystem directories.


## 🚀 Key Features
- 📥 Insert records with unique keys.
- 🗑️ Delete records based on keys.
- 🔍 Search for records using keys.
- 🌐 Display the B-Tree structure.

## 📚 Installation

1. Clone the repository:

   ```bash
   git clone https://github.com/Charantej07/B-Tree-Indexing
   ```
2. Navigate to the repository
   ```bash
   cd B-Tree-Indexing
   ```
3. Compile the source code
   ```bash
   g++ main.cpp B_Tree.cpp -o btree
   ```
4. Run the compiled executable
   ```bash
   ./btree
   ```
## 📁 Code Structure
- 📄 **B_Tree.h:** Header file containing class declarations for Key, Node, and BTree.<br>
- 📄 **B_Tree.cpp:** Implementation file for the BTree class.<br>
- 📄 **main.cpp:** Main program implementing a StorageEngine class for user interaction.<br>

## 🤝 Contributing 
Feel free to contribute by forking the repository and make a pull request.

## 📄 License
This project is licensed under the MIT License.
