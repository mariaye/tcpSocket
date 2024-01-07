#include "tcpSocket.h"

bool init_Socket()
{
	// windows socket async
	// parm1: socket version 2.2 2.1 2.0
	// parm2: return parm
	WSADATA wsadata;
	if (0 != WSAStartup(MAKEWORD(2, 2), &wsadata))
	{
		err("WSAStartup");
		return false;
	}


	return true;
}

bool close_Socket()
{
	if (0 != WSACleanup())
	{
		err("WSACleanup");
		return false;
	}
	return true;
}

SOCKET createServerSocket()
{
	// 1. create empty socket
	// parm1: af address family AF_INET AF_INET6
	// parm2: type SOCK_STREAM
	// parm3: protocol 
	SOCKET fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (fd == INVALID_SOCKET)
	{
		err("create server socket");
		return INVALID_SOCKET;
	}

	// 2. bind socket with ip addr and port
	struct sockaddr_in addr;
	addr.sin_family = AF_INET; // same as the created socket
	addr.sin_port = htons(PORT); // LE TO BE, Host TO Network Short
	addr.sin_addr.S_un.S_addr = ADDR_ANY;// inet_addr("127.0.0.1");
	if (SOCKET_ERROR == bind(fd, &addr, sizeof(addr)))
	{
		err("bind");
		return false;
	}

	// 3. listen
	listen(fd, 10);

	return fd;
}

SOCKET createClientSocket(const char *ip)
{
	// 1. create empty socket
	// parm1: af address family AF_INET AF_INET6
	// parm2: type SOCK_STREAM
	// parm3: protocol 
	SOCKET fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (fd == INVALID_SOCKET)
	{
		err("create client socket");
		return INVALID_SOCKET;
	}

	// 2.  link to server
	struct sockaddr_in addr;
	addr.sin_family = AF_INET; // same as the created socket
	addr.sin_port = htons(PORT); // LE TO BE, Host TO Network Short
	// deprecated: addr.sin_addr.S_un.S_addr = inet_addr(ip); // addr of server
	inet_pton(AF_INET, ip, &addr.sin_addr.S_un.S_addr);
	if (INVALID_SOCKET == connect(fd, (struct sockaddr*)&addr, sizeof(addr)))
	{
		err("connect");
		return false;
	}
	return fd;
}
