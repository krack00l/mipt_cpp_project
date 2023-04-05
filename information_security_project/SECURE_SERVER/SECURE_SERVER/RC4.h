#ifndef RC4_h
#define RC4_h
#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
#include <bitset>


long long getSizeFile(char* filename); // getting the file size (in bytes)
bool RC4Cipher(char* filename1, char* filename2, char* key); // encryption
void printBinaryFile(char* filename); // printing a binary file in the form of zeros and ones (for debug)
void generateKey(char* filename, long long size); // generating a random key of a given length
#endif

