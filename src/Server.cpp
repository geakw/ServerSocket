#include <stdio.h>
#include <winsock2.h>
#include <iostream>

int main(int argc, char* argv[])
{
	//初始化WSA
	WORD sockVersion = MAKEWORD(2, 2);
	WSADATA wsaData;
	if (WSAStartup(sockVersion, &wsaData) != 0)
	{
		return 0;
	}

	//创建套接字
	SOCKET slisten = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (slisten == INVALID_SOCKET)
	{
		printf("socket error !");
		return 0;
	}

	//绑定IP和端口
	sockaddr_in sin;
	sin.sin_family = AF_INET;
	sin.sin_port = htons(8888);
	sin.sin_addr.S_un.S_addr = INADDR_ANY;
	if (bind(slisten, (SOCKADDR *)&sin, sizeof(SOCKADDR)) == SOCKET_ERROR)
	{
		printf("bind error !");
	}

	//开始监听
	if (listen(slisten, 5) == SOCKET_ERROR)
	{
		printf("listen error !");
		return 0;
	}

	//循环接收数据
	SOCKET sClient;
	SOCKADDR_IN buffptr;;
	int nAddrlen = sizeof(SOCKADDR);
	char revData[255];

		std::cout << "Wait for connections...\n";
		sClient = accept(slisten, (SOCKADDR *)&buffptr, &nAddrlen);
		if (sClient == INVALID_SOCKET)
		{
			std::cout << "accept error !";
		}
		std::cout << "Received one connection\n";
		while (true)
		{
		//接收数据
			int ret = recv(sClient, revData, 255, 0);
			if (ret > 0)
			{
				revData[ret] = 0x00;
				std::cout << revData;
				std::cout << "\n";
			}

		//发送数据
//		char * sendData = "Hello, this is TCP Server！\n";
//		send(sClient, sendData, strlen(sendData), 0);
//		closesocket(sClient);
	    }

	closesocket(slisten);
	WSACleanup();
	return 0;
}
