#ifndef handler_request_H
#define handler_request_H
#include "RC4.h"
#include "helper_function.h"
#include "MAPdata.h"
#include <WinSock2.h>
#include <WS2tcpip.h>


#pragma comment(lib, "Ws2_32.lib")

#define GET 'g'
#define PUT 'p'
#define DELETE 'd'
#define DISCONNECTION 'r'
#define ENCRYPTION true

class HandleRequest
{
private:
	std::vector <SOCKET> s_for_connect;
	int index;
public:
	HandleRequest(std::vector <SOCKET> _s_for_connect, int _index);

	static void HandleClient(int index);

	static void send_file(SOCKET sock, std::string& file_name);

	static void recv_file(SOCKET sock);

	static void recv_file_encryption(SOCKET sock);

	static void send_file_decryption(SOCKET sock);
};
#endif // !handler_request_H