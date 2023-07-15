#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable: 4996) // inet_addr
#include <iostream>
#include <winsock2.h>
//#include <cassert>

int main(int argc, char* argv[])
{
	// WSA
	WSAData wsaData;
	WORD DLLVersion = MAKEWORD(2, 1); // Library request
	if (WSAStartup(DLLVersion, &wsaData) != 0) {
		std::cout << "Error: Not updated" << std::endl;
		exit(1);
	}

	SOCKADDR_IN address;
	// int sizeaddress = sizeof(address);
	address.sin_addr.s_addr = inet_addr("127.0.0.1");
	address.sin_port = htons(7777);
	address.sin_family = AF_INET;

	SOCKET connection = socket(AF_INET, SOCK_STREAM, NULL);
	if (connect(connection, (SOCKADDR*)&address, sizeof(address)) != 0) {
		std::cout << "Error: server connection failed\n";
		return 1;
	}

	std::cout << "You are connected to the server \n";
	char message[256];
	recv(connection, message, sizeof(message), NULL);
	std::cout << message << std::endl;

	system("pause");
	return 0;
}