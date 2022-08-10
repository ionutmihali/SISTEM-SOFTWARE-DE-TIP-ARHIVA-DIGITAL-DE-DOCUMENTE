#include <iostream>
#include <WS2tcpip.h>
#include <WinSock2.h>
#include <string>
#pragma comment (lib, "ws2_32.lib")
#include "CServer.h"

using namespace std;

int main()
{
	CServer s("172.16.7.34", 53000);
	s.initWIN();
	SOCKET sock = s.createSocket();
	s.communication(sock);
	s.clean(sock);
	return 0;
}