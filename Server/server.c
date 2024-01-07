#include "../tcpSocket/tcpSocket.h"

int main() 
{
	init_Socket();

	// err("myself");
	
	SOCKET serfd = createServerSocket();
	printf("Waiting for client connection...\n");
	// if there exists client requesting link
	SOCKET clifd = accept(serfd, NULL, NULL);
	if (INVALID_SOCKET == clifd)
	{
		err("accept");
	}
	// commute with client
	// recv receive message from clifd
	char buf[BUFSIZ] = { 0 };
	while (true) {
		memset(buf, 0, BUFSIZ);
		if (0 < recv(clifd, buf, BUFSIZ, 0))
		{
				printf("recv:%s\n", buf);
		}
		memset(buf, 0, BUFSIZ);
		printf("send>");
		gets_s(buf, BUFSIZ);
		if (0 == strcmp(buf, ":serverquit"))
		{
			if (SOCKET_ERROR == send(clifd, "server offline", strlen("server offline"), 0))
			{
				err("send msg to client");
			}
			break;
		}
		else {
			if (SOCKET_ERROR == send(clifd, buf, strlen(buf), 0))
			{
				err("send msg to client");
			}
		}
	}
	
	closesocket(serfd);
	closesocket(clifd);

	close_Socket();
	printf("server----------end---------\n");
	getchar();
	return 0;
}