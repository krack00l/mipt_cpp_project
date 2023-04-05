#include "RC4.h"


bool RC4Cipher(char* filename1, char* filename2, char* key)
{
    std::ifstream file(filename1, std::ios::binary | std::ios::in);
    std::ofstream cipherfile(filename2, std::ios::binary | std::ios::out);
    std::ifstream keyfile(key, std::ios::binary | std::ios::in);

    if ((!file.is_open()) || (!cipherfile.is_open()) || (!keyfile.is_open()))
        return false;

    long long keyLenght = getSizeFile(key);
    std::vector<unsigned char>s(256);

    // initializing the s-block
    for (int i = 0; i < 256; i++) {
        s[i] = i;
    }
    int i, j = 0;
    std::vector<unsigned char>keyarr(256);
    char keybyte;
    int ind = 0;
    while (keyfile.read(&keybyte, sizeof(char)) && ind < 256)
    {
        keyarr[ind++] = keybyte;
    }
    for (i = 0; i < 256; i++)
    {
        j = (j + s[i] + keyarr[i % (int)(keyLenght)]) % 256;
        std::swap(s[i], s[j]);
    }
    i = j = 0;

    //for each byte of the text, we generate a pseudo-random word (byte)
    char byte;
    while (file.read(&byte, sizeof(char))) 
    {
        i = (i + 1) % 256;
        j = (j + s[i]) % 256;
        std::swap(s[i], s[j]);
        unsigned char t = (s[i] + s[j]) % 256;
        unsigned char k = s[t];
        char resbyte = (byte ^ k);
        cipherfile.write(&resbyte, sizeof(char));
    }
    file.close();
    cipherfile.close();
    keyfile.close();
    return true;
}

long long getSizeFile(char* filename) 
{
    std::ifstream file(filename, std::ios::binary);
    file.seekg(0, file.end);
    long long res = file.tellg();
    file.seekg(0, file.beg);
    file.close();
    return res;
}

void printBinaryFile(char* filename) 
{
    std::ifstream file(filename, std::ios::binary);
    char byte;
    while (file.read(&byte, sizeof(char))) 
    {
        std::cout << std::bitset<8>(byte) << " ";
    }
    file.close();
}

void generateKey(char* filename, long long size)
{
    std::ofstream keyfile(filename, std::ios::binary | std::ios::out);
    while (size > 0) 
    {
        char byte = rand() % 256;
        keyfile.write(&byte, sizeof(char));
        size--;
    }
    keyfile.close();
}

