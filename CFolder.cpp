#define _CRT_SECURE_NO_WARNINGS
#include "CFolder.h"
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

int CFolder::verificareExistenta(char* n)
{
	char buff[256];
	ifstream f(this->nume, ios::in);
	while (f.getline(buff, 256))
		if (strcmp(buff, n) == 0)
			return 1;
	return 0;
}

void CFolder::agaugareNume(char* n)
{
	this->nume = string(n);
}

int CFolder::adaugareDocument(char* n, char* co)
{
	int a = verificareExistenta(n);
	if (a == 0)
	{
		int aux = 10;
		ofstream f(this->nume.c_str(), ios::app);
		f << n;
		f << endl;
		CDocument* c = new CDocument(n, aux);
		doc.push_back(c);

		ofstream fout(n, ios::trunc);
		char* p = strtok(co, "*");
		while (p != NULL)
		{
			fout << p;
			p = strtok(NULL, "*");
		}
		nr_documente++;
		f.close();
		fout.close();
		return 0;
	}
	else
	{
		return 1;
	}
}

int CFolder::adaugareDocument(char* n)
{
	int a = verificareExistenta(n);
	if (a == 0)
	{
		int aux = 10;
		ofstream f(this->nume, ios::app);
		f << n;
		f << endl;
		CDocument* c = new CDocument(n, aux);
		doc.push_back(c);

		nr_documente++;
		f.close();
		return 0;
	}
	else {
		return 1;
	}
	
	int aux = 10;
	ofstream f(this->nume, ios::app);
	f << n;
	f << endl;
	CDocument* c = new CDocument(n, aux);
	doc.push_back(c);

	nr_documente++;
	f.close();
	return 0;
}

char* CFolder::veziDocument(int i)
{
	char buff[1000], sent[1000];
	
	char* a = doc.at(i - 1)->getNume();
	char* p = strtok(a, "*\n");
	FILE* f = fopen(p, "r+");
	strcpy(sent, "");
	while (fgets(buff, 1000, f))
	{
		strcat(sent, buff);
		strcat(sent, "|");
	}
	return sent;
	
}

char*  CFolder::veziNume(int i)
{
	char* a = new char[256];
	strcpy(a, doc.at(i - 1)->getNume());
	return a;
}

int CFolder::stergeDocument(char* a, int i)
{
	int aa = verificareExistenta(a);
	if (aa == 1)
	{
		vector<CDocument*>::iterator it = doc.begin() + i - 1;
		doc.erase(it);
		nr_documente = doc.size();
		int aux = 0;

		ofstream f(this->nume.c_str(), ios::trunc);
		while (aux < nr_documente)
		{
			char* a = doc.at(aux)->getNume();
			f << a;
			f << endl;
			aux++;
		}
		return 0;
		f.close();
	}
	else
	{
		return 1;
	}
}

void CFolder::reincarcareDate(char* n)
{
	char buff[30];
	ifstream f(n, ios::app);
	while (f.getline(buff, 30))
	{
		CDocument* c = new CDocument(buff, 10);
		doc.push_back(c);
		nr_documente++;
	}
	
}

int CFolder::getNrDoc()
{
	return doc.size();
}

char* CFolder::numeFolder()
{
	char n[256];
	strcpy(n, this->nume.c_str());
	return n;
}