#ifndef _TCPSOCKET_H_
#define _TCPSOCKET_H_
#include <WinSock2.h>				// windows平台的网络库头文件
#pragma comment(lib, "ws2_32.lib")	// 库文件
#include <WS2tcpip.h>				// inet_pton
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define PORT 12345
#define err(errMsg) printf("[line:%d]%s failed code %d\n", __LINE__, errMsg, WSAGetLastError())


// init
bool init_Socket();

// close
bool close_Socket();

// create server socket
SOCKET createServerSocket();

// create client socket
SOCKET createClientSocket(const char* ip);




#endif // !_TCPSOCKET_H_
