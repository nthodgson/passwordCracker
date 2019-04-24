Password Cracker
---
Spring of 2019

Programmer:
Nathan Hodgson

### Program Description

Given a hashed password, this program uses multithreading to brute force hundreds of thousands of different password hashes and compares them to the hash given to try and find a match. 

### Compilation Specifications

The following command line argument compiles the program:
- gcc main.c -lpthread -o main -g

### Execution Specifications

Run main with the following command line arguments:
1. Name of dictionary file (default dictionary.txt is given)
2. Name of input file (default input.txt is given)
3. Name of output file
4. Number of consumer threads the program will use

### Sample Command Line Arguments

- ./main dictionary.txt input.txt output.txt 5

### Output

- Output file containing the password
