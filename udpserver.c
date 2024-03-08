#pragma comment(lib, "ws2_32.lib")
#include <stdio.h>
#include <WinSock2.h>

void quit(const char* msg) {
	printf("Error: %s\n", msg);
	exit(1);
}

int main(int argc, char** argv) { //take port number from user ; udpserver.exe 12345
	if (argc != 2) quit("Command argument"); // argc = argument count, array of string // argv[0] = "udpserver.exe" and argv[1] = "12345"
	WSADATA w;
	int ret = WSAStartup(MAKEWORD(2, 2), &w);
	if (ret == 1) quit("Winsock API"); 
	SOCKET s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (s == SOCKET_ERROR) quit("Create socket");
	printf("Socket is ready\n");
	SOCKADDR_IN sa; //local socket address // 0.0.0.0 = any address
	sa.sin_addr.s_addr = INADDR_ANY;
	sa.sin_port = htons(atoi(argv[1]));		//htons changes endiness
	sa.sin_family = AF_INET;
	ret = bind(s, (SOCKADDR*)&sa, sizeof(sa));
	if (ret == SOCKET_ERROR) quit("binding");
	printf("binding is okay\n");
	while (1);

}