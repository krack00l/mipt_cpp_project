#include "handler_request.h"


class HandleRequest
{
private:
	std::vector <SOCKET> s_for_connect;
	int index;
	MAPData data;
public:
	HandleRequest(std::vector <SOCKET> _s_for_connect, int _index) : index(_index), s_for_connect(_s_for_connect)
	{
		std::cout << "hey!" << std::endl;
	}

	void HandleClient(int index)
	{
		std::cout << index << std::endl;
		std::cout << "HandleClient success work" << std::endl;
		int file_size;
		char type_request[3];
		char file_id[32];
		std::string buff = "";
		int i = 0;
		if (ENCRYPTION)
		{
			while (true)
			{
				recv(this->s_for_connect[index], type_request, 3, 0);
				//std::cout << "type request:\t" << type_request << std::endl;
				switch (type_request[0])
				{
				case GET:
					std::cout << "Handle recieve get" << std::endl;
					recv(s_for_connect[index], file_id, 32, 0);
					std::cout << file_id << std::endl;
					buff = std::string(file_id);
					std::cout << buff << std::endl;
					send_file(s_for_connect[index], buff);
					buff = "";
					break;
				case PUT:
					std::cout << "Handle recieve put" << std::endl;
					recv_file(s_for_connect[index]);
					break;
				case DELETE:
					std::cout << "Handle recieve delete" << std::endl;
					this->data.backup();
					break;
				case DISCONNECTION:
					std::cout << "Handle recieve Disconection" << std::endl;
					break;
				default:
					std::cout << "While don't recive request from client" << std::endl;
					break;
				}
				type_request[0] = '0';
			}
		}
		else
		{
			std::cout << "ewreofjierjpvknad;jbfdghjjgfhdgsffdgficslprkofl" << std::endl;
			while (true)
			{
				recv(s_for_connect[index], type_request, 3, 0);
				std::cout << "type reqeuest:\t" << type_request << std::endl;
				switch (type_request[0])
				{
				case GET:
					std::cout << "Handle recieve get" << std::endl;
					recv(s_for_connect[index], file_id, 32, 0);
					std::cout << file_id << std::endl;
					buff = std::string(file_id);
					std::cout << buff << std::endl;
					send_file_decryption(s_for_connect[index], buff);
					buff = "";
					type_request[0] = '0';
					system("pause");
					break;
				case PUT:
					std::cout << "Handle recieve put" << std::endl;
					recv_file_encryption(s_for_connect[index]);
					type_request[0] = '0';
					break;
				case DELETE:
					std::cout << "Handle recieve delete" << std::endl;
					break;
				case DISCONNECTION:
					std::cout << "Handle recieve Disconection" << std::endl;
					break;
				default:
					std::cout << "While don't recive request from client" << std::endl;
					break;
				}
				type_request[0] = '0';
			}
		}
	}

	void send_file(SOCKET sock, std::string& file_name)
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

			send(sock, std::to_string(file_size).c_str(), 16, 0);
			send(sock, file_name.c_str(), 32, 0);
			send(sock, bytes, file_size, 0);

		}
		else
			std::cout << "Error file open\n";

	}

	void recv_file(SOCKET sock)
	{
		char file_size_str[16];
		char file_name[32];

		recv(sock, file_size_str, 16, 0);
		int file_size = atoi(file_size_str);
		char* bytes = new char[file_size];

		recv(sock, file_name, 32, 0);

		std::fstream file;
		file.open(file_name, std::ios_base::out | std::ios_base::binary);

		std::cout << "size: " << file_size << std::endl;
		std::cout << "name: " << file_name << std::endl;

		if (file.is_open())
		{
			recv(sock, bytes, file_size, 0);
			file.write(bytes, file_size);
			std::cout << "ok save\n";
		}
		else
			std::cout << "Error file open\n";

		delete[] bytes;
		file.close();
	}

	void recv_file_encryption(SOCKET sock)
	{
		std::cout << "this fork encryption" << std::endl;
		std::string buff_file_name = "buffer";
		char file_size_str[16];
		char file_name[32];
		char file_name_length[16];

		recv(sock, file_size_str, 16, 0);

		recv(sock, file_name_length, 16, 0);
		int file_size = atoi(file_size_str);
		int name_size = atoi(file_name_length);
		char* bytes = new char[file_size];

		recv(sock, file_name, name_size, 0);

		std::fstream file;
		std::fstream file_buff;
		file_buff.open(file_name, std::ios_base::out | std::ios_base::binary);

		std::cout << "size: " << file_size << std::endl;
		std::cout << "name: " << file_name << std::endl;

		if (file_buff.is_open())
		{
			recv(sock, bytes, file_size, 0);
			file_buff.write(bytes, file_size);
			file_buff.close();
			std::string rand_key = std::to_string(rand());
			std::string key_file = rand_key + "key.rtf";
			std::string file_name_encryption = rand_key + "res.rtf";
			data.AddFileInfo(rand_key, get_extension(file_name), key_file);
			generateKey((char*)key_file.c_str(), 256);
			bool resOperation = RC4Cipher((char*)(std::string(file_name).c_str()), (char*)file_name_encryption.c_str(), (char*)key_file.c_str());//само шифрование
			if (resOperation)
				std::cerr << "falture in RC4Chipher";
			std::cout << "ok save\n";

			//sending an identifier to the client
			send(sock, (char*)(std::to_string((rand_key.length())).c_str()), 16, 0);
			send(sock, (char*)rand_key.c_str(), rand_key.length(), 0);
		}
		else
			std::cout << "Error file open\n";

		std::remove(buff_file_name.c_str());
		delete[] bytes;
		file.close();
		file_buff.close();
	}

	void send_file_decryption(SOCKET sock, std::string file_id)
	{
		std::cout << "i need your help" << std::endl;
	}
};