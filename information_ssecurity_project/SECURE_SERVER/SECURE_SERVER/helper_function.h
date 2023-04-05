#ifndef helper_function_H
#define helper_function_H
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <WinSock2.h>
#include <WS2tcpip.h>

#pragma comment(lib, "Ws2_32.lib")

std::string int_to_string(int a);
std::string GenRandomId(std::string path);
void increase(SOCKET* sock, int& COUNT_CONNECT);
std::ifstream::pos_type filesize(const char* filename);
std::string get_extension(char* file_name);
#endif // !helper_function_H