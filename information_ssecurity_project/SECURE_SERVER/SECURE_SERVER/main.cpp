#include "RC4.h"
#include "MAPdata.h"
#include "handler_request.h"
#include <iostream>
#include <fstream>
#include <chrono>
#include <filesystem>
#include <map>
#include <vector>
#include <string>
#include <random>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <stdlib.h>
#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>


#pragma comment(lib, "Ws2_32.lib")

#define GET 'g'
#define PUT 'p'
#define DELETE 'd'
#define DISCONNECTION 'r'
#define ENCRYPTION true

int COUNT_CONNECT = 1;
std::vector <SOCKET> s_for_connect;
MAPData data = MAPData();

void handle_request(int index)
{
	std::cout << "I'm work" << std::endl;
	HandleRequest handle_client = HandleRequest(s_for_connect, index);
	handle_client.HandleClient(index);
}

int main()
{
	//initialization
	MAPData data_in = MAPData();
	data = data_in;
	int number_connection = 0;
	WORD dllVer = MAKEWORD(2, 1);
	WSADATA wsad;

	WSAStartup(dllVer, &wsad);
	SOCKADDR_IN addr_info;
	memset(&addr_info, 0, sizeof(SOCKADDR_IN));

	int size_addr = sizeof(addr_info);
	addr_info.sin_port = htons(4321);
	addr_info.sin_family = AF_INET;

	SOCKET s_listen = socket(AF_INET, SOCK_STREAM, 0);
	bind(s_listen, (sockaddr*)&addr_info, sizeof(addr_info));
	listen(s_listen, SOMAXCONN);


	do
	{
		s_for_connect.push_back(accept(s_listen, (sockaddr*)&addr_info, &size_addr));
		std::cout << "success";
		std::cout << number_connection << " " << "CONNECT" << std::endl;
		number_connection++;
		COUNT_CONNECT++;
		CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)handle_request, (LPVOID)(number_connection - 1), NULL, NULL);
	} while (true);



	std::system("pause");
	return 0;
}