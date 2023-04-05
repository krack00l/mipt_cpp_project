#include "helper_function.h"


void increase(SOCKET* sock, int& COUNT_CONNECT) 
{
	COUNT_CONNECT = COUNT_CONNECT + 1;
	SOCKET* buff_sock = new SOCKET[COUNT_CONNECT];
	for (int i = 0; i < COUNT_CONNECT - 1; i++)
		buff_sock[i] = sock[i];
	buff_sock[COUNT_CONNECT - 1] = NULL;
	delete[] sock;
	sock = nullptr;
	sock = buff_sock;
}

std::string int_to_string(int a)
{
	std::string buff = "";
	while (a != 0)
	{
		char c;
		switch (a % 10)
		{
		case 0:
			c = '0';
			break;
		case 1:
			c = '1';
			break;
		case 2:
			c = '2';
			break;
		case 3:
			c = '3';
			break;
		case 4:
			c = '4';
			break;
		case 5:
			c = '5';
			break;
		case 6:
			c = '6';
			break;
		case 7:
			c = '7';
			break;
		case 8:
			c = '8';
			break;
		case 9:
			c = '9';
			break;
		default:
			break;
		}
		buff = c + buff;
		a /= 10;
	}
	return buff;
}

std::string GenRandomId(std::string path)
{
	return path;
}

std::ifstream::pos_type filesize(const char* filename)
{
	std::ifstream in(filename, std::ifstream::ate | std::ifstream::binary);
	return in.tellg();
}

std::string get_extension(char* file_name)
{
	int i = 0;
	std::string buff = "";
	while (file_name[i] != '\0')
	{
		if (file_name[i] == '.')
		{
			while (file_name[i] != '\0')
			{
				buff = buff + file_name[i];
				i++;
			}
		}
		else
			i++;
	}

	return buff;
}