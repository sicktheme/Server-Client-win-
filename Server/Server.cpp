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
	int sizeaddress = sizeof(address);
	address.sin_addr.s_addr = inet_addr("127.0.0.1");
	address.sin_port = htons(7777);
	address.sin_family = AF_INET;

	SOCKET wiretapping = socket(AF_INET, SOCK_STREAM, NULL);
	bind(wiretapping, (SOCKADDR*)&address, sizeof(address));
	listen(wiretapping, SOMAXCONN);
	 
	SOCKET newConnection;
	newConnection = accept(wiretapping, (SOCKADDR*)&address, &sizeaddress);

	if (newConnection == 0) {
		std::cout << "Error: the client was unable to connect to the server\n";
	}
	else {
		std::cout << "Client connected\n";
		char message[256] = "Hello, client";
		send(newConnection, message, sizeof(message), NULL);
	}

	return 0;
}
