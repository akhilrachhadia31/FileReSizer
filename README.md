# FileReSizer

**FileReSizer** is a powerful and efficient C++ tool designed for compressing and decompressing files using the **Huffman Coding Algorithm**. Whether you're looking to save storage space, reduce data transmission time, or manage large files effectively, FileReSizer offers a reliable, lossless compression solution with detailed feedback and a simple command-line interface.

---

##  Features

- Huffman Compression Algorithm   
  Compresses files using the efficient Huffman coding technique.

-  Decompression Support  
  Accurately restores compressed files to their original content.

-  Compression Ratio Display  
  Shows original vs. compressed file sizes with percentage compression.

-  Supports Various File Types  
  Works with text and binary files alike.

-  User-Friendly CLI Interface  
  Clean, interactive terminal interface.

-  Execution Time Tracking  
  Displays how long compression or decompression took.

---

## 📁 Required Files

Make sure the following files are present in your project directory:

- `Unit_Huffman.hpp` — Header file implementing the Huffman algorithm
- `FileReSizer.cpp` — Main file containing the user interface and logic

---

## 🔧 How to Compile and Run

### 1. Open Terminal or PowerShell in the project directory

### 2. Compile the program:

```bash
g++ FileReSizer.cpp -o FileReSizer
```

### 3. Run the executable:
```
./FileReSizer
```

### Sample Output
```
--> Enter 1 for Compressing a file.
--> Enter 2 for Decompressing a file.
--> Enter 3 for Exiting.
1

Enter the source file name to be compressed: test.txt
Enter the destination file name to save compressed file: test1.txt

Compressed Successfully to file: test1.txt
Time taken: 1.072 sec
File Size Before Compressing: 162016 Bytes
File Size After Compressing: 103481 Bytes
The size of compressed file is 63.87% of the original file.

--> Enter 1 for Compressing a file.
--> Enter 2 for Decompressing a file.
--> Enter 3 for Exiting.
2

Enter the compressed source file name: test1.txt
Enter the destination file name to save decompressed data: test2.txt

File Size After Decompressing: 163079 Bytes
Decompressed Successfully to file: test2.txt
Time taken: 2.08 sec

--> Enter 1 for Compressing a file.
--> Enter 2 for Decompressing a file.
--> Enter 3 for Exiting.
3

Thank You! Have A Nice Day.
```
### 📌 Notes
- Compressed files are saved with your chosen name.
- No internet or external dependencies required.
- Huffman compression is lossless, meaning the original data is perfectly recoverable.

### 👨‍💻 Author
-  Akhil Rachhadia
-  Email: akhilrachhadia311003@gmail.com
