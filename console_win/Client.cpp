#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define NTDDI_VERSION NTDDI_VISTA
#define WINVER _WIN32_WINNT_VISTA
#define _WIN32_WINNT _WIN32_WINNT_VISTA

#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <strsafe.h>
#include <iostream>
#include <string>
#include <WinSock2.h>
#include <WS2tcpip.h>

#pragma comment(lib, "Ws2_32.lib")

#define BUFSIZE 4096
#define SERVER_IP "127.0.0.1"

SOCKET clientSocket = NULL;

int main()
{
    WSADATA wsData;
    int erStat = WSAStartup(MAKEWORD(2, 2), &wsData);
    if (erStat != 0)
    {
        std::cout << "Error WinSock version initializaion #";
        std::cout << WSAGetLastError();
        return 1;
    }
    else
        std::cout << "WinSock initialization is OK" << std::endl;

    clientSocket = socket(AF_INET, SOCK_DGRAM, 0);

    if (clientSocket == INVALID_SOCKET)
    {
        std::cout << "Error initialization socket # " << WSAGetLastError() << std::endl;
        closesocket(clientSocket);
        WSACleanup();
        return 1;
    }
    else
        std::cout << "Server socket initialization is OK" << std::endl;

    in_addr ip_to_num;
    erStat = inet_pton(AF_INET, SERVER_IP, &ip_to_num);
    if (erStat <= 0)
    {
        std::cout << "Error in IP translation to special numeric format" << std::endl;
        return 1;
    }

    char val = 1;
    if (setsockopt(clientSocket, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(int)) < 0)
        return 1;
    sockaddr_in clientInfo;
    sockaddr_in serverInfo;
    ZeroMemory(&clientInfo, sizeof(clientInfo));
    ZeroMemory(&serverInfo, sizeof(serverInfo));

    clientInfo.sin_family = AF_INET;
    clientInfo.sin_addr = ip_to_num;
    clientInfo.sin_port = htons(2222);

    serverInfo.sin_family = AF_INET;
    serverInfo.sin_addr = ip_to_num;
    serverInfo.sin_port = htons(1111);

    int serverInfoSize = sizeof(serverInfo);

    erStat = bind(clientSocket, (sockaddr *)&clientInfo, sizeof(clientInfo));
    if (erStat != 0)
    {
        std::cout << "Error Socket binding to server info. Error # " << WSAGetLastError() << std::endl;
        closesocket(clientSocket);
        WSACleanup();
        return 1;
    }
    else
        std::cout << "Binding socket to Server info is OK" << std::endl;

    std::string input;
    std::cin >> input;

    erStat = sendto(clientSocket, input.c_str(), input.length(), NULL, (sockaddr *)&serverInfo, serverInfoSize);

    return 0;
}
