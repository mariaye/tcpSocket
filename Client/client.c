#include "../tcpSocket/tcpSocket.h"

int main() {

	init_Socket();

	SOCKET fd = createClientSocket("127.0.0.1");
	// send msg to server
	char buf[BUFSIZ] = "Hello World!";
	if (SOCKET_ERROR == send(fd, buf, strlen(buf), 0))
	{
		err("send msg to server");
	}
	while (true)
	{
		memset(buf, 0, BUFSIZ);
		if (0 < recv(fd, buf, BUFSIZ, 0))
		{
			printf("recv:%s\n", buf);
		}
		memset(buf, 0, BUFSIZ);
		printf("send>");
		gets_s(buf, BUFSIZ);
		if (0 == strcmp(buf, ":clientquit"))
		{
			if (SOCKET_ERROR == send(fd, "client offline", strlen("client offline"), 0))
			{
				err("send msg to client");
			}
			break;
		}
		else {
			if (SOCKET_ERROR == send(fd, buf, strlen(buf), 0))
			{
				err("send msg to server");
			}
		}
	}
	

	closesocket(fd);
	close_Socket();
	printf("client----------end---------\n");
	getchar();
	return 0;
}