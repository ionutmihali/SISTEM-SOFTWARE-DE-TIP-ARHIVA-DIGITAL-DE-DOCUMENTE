#include "IServer.h"
#include<WS2tcpip.h>
#include<WinSock2.h>
#include<string>
#pragma comment(lib,"ws2_32.lib")
#include <string.h>
#include "CUser.h"
#include <iostream>
using namespace std;

class CServer :
    public IServer
{
private:
    string ipaddress;
    int port;

public:
    CServer(string, int);
    void initWIN();
    SOCKET createSocket();
    void communication(SOCKET &listening);
    void clean(SOCKET client);

};
