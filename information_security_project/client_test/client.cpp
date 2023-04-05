#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <WinSock2.h>
#include <WS2tcpip.h>
#include <iostream>
#include <fstream>
#include <filesystem>

#pragma comment(lib, "Ws2_32.lib")


std::ifstream::pos_type filesize(const char* filename);
void recv_file(SOCKET* sock);
void send_file(SOCKET* sock, const std::string& file_name);


int main()
{
	WORD dllVer = MAKEWORD(2, 1);
	WSADATA wsad;

	WSAStartup(dllVer, &wsad);
	SOCKADDR_IN addr_info;
	memset(&addr_info, 0, sizeof(SOCKADDR_IN));

	addr_info.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	addr_info.sin_port = htons(4321);
	addr_info.sin_family = AF_INET;

	SOCKET s_client = socket(AF_INET, SOCK_STREAM, 0);

	if (connect(s_client, (sockaddr*)&addr_info, sizeof(addr_info)) == 0)
	{
		
		std::cout << "CONNECT\n";
		std::string file_name = "SERVER_2.vcxproj.filters";
		std::string type = "put";
		std::system("pause");
		type = "rec";

		std::system("pause");
		type = "put";
		file_name = "SimpleServer.vcxproj";
		send(s_client, type.c_str(), 3, 0);
		send_file(&s_client, file_name);
	}
	else
		std::cout << "NOT CONNECT\n";

	std::system("pause");

	return 0;
}


std::ifstream::pos_type filesize(const char* filename)
{
	std::ifstream in(filename, std::ifstream::ate | std::ifstream::binary);
	return in.tellg();
}
void recv_file(SOCKET* sock)
{
	char file_size_str[16];
	char file_name[32];

	recv(*sock, file_size_str, 16, 0);
	int file_size = atoi(file_size_str);
	char* bytes = new char[file_size];

	recv(*sock, file_name, 32, 0);

	std::fstream file;
	file.open(file_name, std::ios_base::out | std::ios_base::binary);

	std::cout << "size: " << file_size << std::endl;
	std::cout << "name: " << file_name << std::endl;

	if (file.is_open())
	{
		recv(*sock, bytes, file_size, 0);
		std::cout << "data: " << bytes << std::endl;

		file.write(bytes, file_size);
		std::cout << "ok save\n";
	}
	else
		std::cout << "Error file open\n";

	delete[] bytes;
	file.close();
}
void send_file(SOCKET* sock, const std::string& file_name)
{
	std::fstream file;
	file.open(file_name, std::ios_base::in | std::ios_base::binary);

	if (file.is_open())
	{
		int file_size = filesize(file_name.c_str());
		file_size++;

		char* bytes = new char[file_size];

		file.read((char*)bytes, file_size);

		std::cout << "size: " << file_size << std::endl;
		std::cout << "name: " << file_name << std::endl;
		std::cout << "data: " << bytes << std::endl;

		send(*sock, std::to_string(file_size).c_str(), 16, 0);
		send(*sock, std::to_string(file_name.length()).c_str(), 16, 0);
		send(*sock, file_name.c_str(), 32, 0); //why not length
		send(*sock, bytes, file_size, 0);

		char key_size[16];
		recv(*sock, key_size, 16, 0);
		int s = atoi(key_size);
		char* k = new char[s];
		recv(*sock, k, s, 0);



	}
	else
		std::cout << "Error file open\n";

}