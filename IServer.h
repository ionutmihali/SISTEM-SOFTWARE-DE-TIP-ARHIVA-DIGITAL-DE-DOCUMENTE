#pragma once
#include<WS2tcpip.h>
#include<WinSock2.h>
#include<string>
#pragma comment(lib,"ws2_32.lib")

class IServer
{
private:
    virtual void initWIN() = 0;
    virtual SOCKET createSocket() = 0;
    virtual void communication(SOCKET &listening) = 0;
    virtual void clean(SOCKET client) = 0;
};

