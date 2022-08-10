#define _CRT_SECURE_NO_WARNINGS
#include "CServer.h"
#include <iostream>
#include <fstream>
using namespace std;

void verif(SOCKET &cl, int a)
{
	if (a == 0)
		send(cl, "0", 256, 0);
	else if (a == 1)
		send(cl, "1", 256, 0);
}

CServer::CServer(string a, int b)
{
	this->ipaddress = a;
	this->port = b;
}

void CServer::initWIN()
{
	//Initializare winsock
	WSADATA wsDATA;
	WORD ver = MAKEWORD(2, 2);

	int wsOk = WSAStartup(ver, &wsDATA);
	if (wsOk != 0)
	{
		cout << "Cant't initialize winsock! Quitting" << endl;
		return;
	}
}

SOCKET CServer::createSocket()
{
	//creare socket
	SOCKET listening = socket(AF_INET, SOCK_STREAM, 0);
	if (listening == INVALID_SOCKET)
	{
		cout << "Can't create socket! Quitting" << endl;
		return 0;
	}

	//atribuire adresa --are doar adresa familiei din care face parte
	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(port);
	inet_pton(AF_INET, ipaddress.c_str(), &hint.sin_addr);

	bind(listening, (sockaddr*)&hint, sizeof(hint)); //asigneaza o adresa locala pentru socket

	//tell winsock the socket is for listening
	listen(listening, SOMAXCONN); //disponibilitatea de a primii cereri de la client --cand e plina, restul sunt respinse

	//asteapta conexiunea cu clientul
	sockaddr_in client;
	
	int clientSize = sizeof(client);

	SOCKET clientSocket = accept(listening, (sockaddr*)&client, &clientSize); //se creeaza conexiunea cu clientul--accepta conexiunea
	if (clientSocket == INVALID_SOCKET)
	{
		cerr << "Can't create socket! Quitting" << endl;
		return 0;
	}
	return clientSocket;
}
void CServer::communication(SOCKET &cl)
{
	char buf[1000];
	ZeroMemory(buf, 1000);
	int ok = 1;
	CUser* u = new CUser("", "");

	//Wait for client to send data
	while (ok == 1)
	{
		recv(cl, buf, 1000, 0);
		cout << "CLIENT> " << buf << endl;
		/*if (bytesReceived == SOCKET_ERROR)
		{
			cerr << "Error in recv(). Quitting" << endl;
			break;
		}*/
		/*if (bytesReceived == SOCKET_ERROR)
		{
			cout << "Client diconnected " << endl;
			return;
		}*/

		char* p = strtok(buf, "|\n");
		if (strcmp(buf, "0") == 0)
		{
			char user[20], parola[20], buffer[20];
			p = strtok(NULL, "|\n");
			strcpy(user, p);
			p = strtok(NULL, "|\n");
			strcpy(parola, p);
			fstream f;
			f.open("Logare.txt");
			int ok = 0;
			while (f.getline(buffer, 20))
			{
				char* p1 = strtok(buffer, " \n");
				char* p2 = p1;
				p1 = strtok(NULL, " \n");
				if (strcmp(user, p2) == 0 && strcmp(parola, p1) == 0)
				{
					send(cl, "0", 256, 0);
					ok++;
					u->setNume(user);
					u->setParola(parola);
					u->reincarcareDate();
					break;
				}
				else if (strcmp(user, p2) == 0 && strcmp(parola, p1) != 0)
				{
					send(cl, "1", 256, 0);
					ok++;
					break;
				}
				else if (strcmp(user, p2) != 0)
				{
					send(cl, "2", 256, 0);
					ok++;
					break;
				}
			}
			if(ok==0)
				send(cl, "3", 256, 0);
			f.close();
		}
		else if (strcmp(buf, "1") == 0)
		{
			char user[20], buffer[20], parola[20];
			char a[50];
			p = strtok(NULL, "|\n");
			strcpy(user, p);
			p = strtok(NULL, "|\n");
			strcpy(parola, p);
			strcpy(a, "");
			strcat(a, user);
			strcat(a, " ");
			strcat(a, parola);
			ifstream f("Logare.txt");
			int ok = 0;
			while (f.getline(buffer, 20))
			{
				char* p1 = strtok(buffer, " \n");
				char* p2 = p1;
				p1 = strtok(NULL, " \n");
				if (strcmp(user, p2) != 0)
				{
					send(cl, "0", 256, 0);
					ok++;
					break;
				}
				else if (strcmp(user, p2) == 0)
					send(cl, "1", 256, 0);
			}
			f.close();
			if (ok != 0)
			{
				ofstream fout("Logare.txt", ios::app);
				fout << endl;
				fout << a;
				u->setNume(user);
				u->setParola(parola);
				u->creareFoldereInitiale();
				u->setAbonament();
			}
		}
		else if (strcmp(buf, "2") == 0)
		{
			send(cl, "0", 256, 0);
			ok = 0;
		}
		else if (strcmp(buf, "3") == 0)
		{
			char s[256];
			strcpy(s, "0|");
			strcat(s, u->getDocMele());
			send(cl, s, 256, 0);
		}
		else if (strcmp(buf, "4") == 0)
		{
			char s[256];
			strcpy(s, "0|");
			strcat(s, u->getDocPref());
			send(cl, s, 256, 0);
		}
		else if (strcmp(buf, "5") == 0)
		{
			p = strtok(NULL, "|\n");
			char nume[20];
			strcpy(nume, p);
			p = strtok(NULL, "|");
			char continut[2000];
			strcpy(continut, p);
			int a = u->adaugareDocument(nume, continut);
			verif(cl, a);
		}
		else if (strcmp(buf, "6") == 0)
		{
			p = strtok(NULL, "|\n");			
			int i = atoi(p);
			int a = u->cosDocumentMele(i);
			verif(cl, a);
		}
		else if (strcmp(buf, "7") == 0)
		{
			char s[1000];
			p = strtok(NULL, "|\n");
			int i = atoi(p);
			strcpy(s, "0|");
			strcat(s, u->veziDocument(i));
			send(cl, s, 1000, 0);
		}
		else if (strcmp(buf, "8") == 0)
		{
		char* a = u->detaliiCont();
		send(cl, a, 256, 0);
		}
		else if (strcmp(buf, "10") == 0)
		{
		p = strtok(NULL, "|\n");
		int i = atoi(p);
		p = strtok(NULL, "|\n");
		char b[256];
		strcpy(b, p);
		int a = u->mutaDoc(i, b);
		verif(cl, a);
		}
		else if (strcmp(buf, "11") == 0)
		{
			p = strtok(NULL, "|\n");
			int i = atoi(p);
			int a = u->favDocument(i);
			verif(cl, a);
		}
		else if (strcmp(buf, "12") == 0)
		{
		p = strtok(NULL, "|\n");
		int i = atoi(p);
		int a = u->unfavDocument(i);
		verif(cl, a);
		}
		else if (strcmp(buf, "15") == 0)
		{
		p = strtok(NULL, "|\n");
		int a = u->creareFolder(p);
		verif(cl, a);
		//send(cl, "0", 256, 0);
		}
		else if (strcmp(buf, "17") == 0)
		{
			p = strtok(NULL, "|\n");
			int i = atoi(p);
			int a = u->stergeDocument(i);
			verif(cl, a);
		}
		else if (strcmp(buf, "18") == 0)
		{
			p = strtok(NULL, "|\n");
			u->golesteCos();
			send(cl, "0", 256, 0);
		}
		else if (strcmp(buf, "20") == 0)
		{
		char s[256];
		strcpy(s, "0|");
		strcat(s, u->getDocCos());
		send(cl, s, 256, 0);
		}
		else if (strcmp(buf, "21") == 0)
		{
		p = strtok(NULL, "|\n");
		int i = atoi(p);
		int a = u->recoverDocument(i);
		verif(cl, a);
		}
		else if (strcmp(buf, "22") == 0)
		{
		p = strtok(NULL, "|\n");
		u->updateAbonament();
		send(cl, "0", 256, 0);
		}
	}
}

void CServer::clean(SOCKET client)
{
	//Inchidere socket
	closesocket(client);

	//Inchidere winsock
	WSACleanup();
}