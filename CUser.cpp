#define _CRT_SECURE_NO_WARNINGS
#include "CUser.h"
#include "string.h"
#include <stdio.h>
#include <fstream>
using namespace std;

CUser::CUser(string a, string b)
{
	this->nume = a;
	this->parola = b;
	this->dimensiune = 0;
}

void CUser::setNume(char n[])
{
	this->nume = string(n);
}

void CUser::setParola(char p[])
{
	this->parola = string(p);
}

void CUser::setAbonament()
{
	CAbonament* c = new CAbonament();
	this->abonament = c;

	ofstream f("Detalii.txt", ios::app);
	f << this->nume;
	f << " ";
	char a[256];
	strcpy(a, this->abonament->getNume().c_str());
	int b = this->abonament->getDim();
	int d = this->abonament->getValoare();
	f << b << " " << d << endl;
	f.close();
}

char* CUser::getDocMele()
{
	char n[500], buff[50];
	strcpy(n, "");
	strcat(n, this->nume.c_str());
	strcat(n, "_DocMele.txt");
	ifstream f(n);
	char sent[500];
	strcpy(sent, "");
	while (f.getline(buff, 50))
	{
		strcat(sent, buff);
		strcat(sent, "|");
	}



	return sent;
}

char* CUser::getDocPref()
{
	char n[500], buff[50];
	strcpy(n, "");
	strcat(n, this->nume.c_str());
	strcat(n, "_DocFav.txt");
	ifstream f(n);
	char sent[500];
	strcpy(sent, "");
	while (f.getline(buff, 50))
	{
		strcat(sent, buff);
		strcat(sent, "|");
	}
	return sent;
}

char* CUser::getDocCos()
{
	char n[500], buff[50];
	strcpy(n, "");
	strcat(n, this->nume.c_str());
	strcat(n, "_Cos.txt");
	ifstream f(n);
	char sent[500];
	strcpy(sent, "");
	while (f.getline(buff, 50))
	{
		strcat(sent, buff);
		strcat(sent, "|");
	}
	return sent;
}

void CUser::creareFoldereInitiale()
{
	//Documentele mele
	char n[500];
	strcpy(n, "");
	strcat(n, this->nume.c_str());
	strcat(n, "_DocMele.txt");
	FILE* f1 = fopen(n, "w+");
	fclose(f1);
	dm = new CFolderUser();
	dm->agaugareNume(n);

	//Documente favorite
	strcpy(n, "");
	strcat(n, this->nume.c_str());
	strcat(n, "_DocFav.txt");
	FILE* f2 = fopen(n, "w+");
	fclose(f2);
	df = new CFolderFavorite();
	df->agaugareNume(n);

	//Cos de gunoi
	strcpy(n, "");
	strcat(n, this->nume.c_str());
	strcat(n, "_Cos.txt");
	FILE* f3 = fopen(n, "w+");
	fclose(f3);
	cos = new CFolderCos();
	cos->agaugareNume(n);
}

void CUser::incarcareDetalii()
{
	char buff[256];
	FILE* f = fopen ("Detalii.txt", "r");
	CAbonament* abo = new CAbonament();
	this->abonament = abo;
	while (fgets(buff, 256, f))
	{
		char* p = strtok(buff, " \n");
		if (strcmp(p, this->nume.c_str()) == 0)
		{
			p = strtok(NULL, " \n");
			char a[256];
			int b, c;
			strcpy(a, p);
			p = strtok(NULL, " \n");
			b = atoi(p);
			p = strtok(NULL, " \n");
			c = atoi(p);
			this->abonament->updateAbonament(a, b, c);
		}
	}
}

void CUser::reincarcareDate()
{
	//Documentele mele
	char n[500];
	strcpy(n, "");
	strcat(n, this->nume.c_str());
	strcat(n, "_DocMele.txt");
	dm = new CFolderUser();
	dm->agaugareNume(n);
	dm->reincarcareDate(n);

	//Documente favorite
	strcpy(n, "");
	strcat(n, this->nume.c_str());
	strcat(n, "_DocFav.txt");
	df = new CFolderFavorite();
	df->agaugareNume(n);
	df->reincarcareDate(n);

	//Cos de gunoi
	strcpy(n, "");
	strcat(n, this->nume.c_str());
	strcat(n, "_Cos.txt");
	cos = new CFolderCos();
	cos->agaugareNume(n);
	cos->reincarcareDate(n);

	//detalii
	incarcareDetalii();

	//Foldere
	char buff[256];
	strcpy(n, "");
	strcat(n, this->nume.c_str());
	strcat(n, "_Folder.txt");
	ifstream f(n, ios::app);
	while (f.getline(buff, 256))
	{
		CFolder* fo = new CFolder(buff);
		folder.push_back(fo);
	}
	f.close();

}

int CUser::adaugareDocument(char* n, char* c)
{
	int a1 = dm->adaugareDocument(n, c);
	if (a1 == 0)
		dimensiune += 10;
	return a1;
}

char* CUser::veziDocument(int i)
{
	char* sent = dm->veziDocument(i);
	return sent;
}

int CUser::favDocument(int i)
{
	int aux1 = dm->getNrDoc();
	if (i > aux1)
		return 1;
	char* a = dm->veziNume(i);
	int aux = dm->getNrDoc();
	int a1 = df->adaugareDocument(a);
	return a1;
}

int CUser::unfavDocument(int i)
{
	int aux = df->getNrDoc();
	if (i > aux)
		return 1;
	char* a = df->veziNume(i);
	int a1 = df->stergeDocument(a, i);
	return a1;
}

int CUser::cosDocumentMele(int i)
{
	int aux = dm->getNrDoc();
	if (i > aux)
		return 1;
	char* a = dm->veziNume(i);
	int a1 = cos->adaugareDocument(a);
	int a2 = dm->stergeDocument(a, i);
	if (a1 == 0 && a2 == 0)
		return 0;
	return 1;
}

int CUser::recoverDocument(int i)
{
	int aux = dm->getNrDoc();
	if (i > aux)
		return 1;
	char* a = cos->veziNume(i);
	int a1 = dm->adaugareDocument(a);
	int a2 = cos->stergeDocument(a, i);
	if (a1 == 0 && a2 == 0)
		return 0;
	return 1;
}

int CUser::stergeDocument(int i)
{
	int aux = cos->getNrDoc();
	if (i > aux)
		return 1;
	char* a = cos->veziNume(i);
	int a1 = cos->stergeDocument(a, i);
	if (a1 == 0)
		dimensiune -= 10;
	return a1;
}

void CUser::golesteCos()
{
	cos->golesteCos();
}

char* CUser::detaliiCont()
{
	int a = this->dm->getNrDoc();
	this->dimensiune = a * 10;
	char buff[256], aux[256]="";
	strcpy(buff, "");
	strcat(buff, "0|");
	strcat(buff, this->nume.c_str());
	strcat(buff, "|");
	strcat(buff, this->abonament->getNume().c_str());
	strcat(buff, "|");
	_itoa(this->abonament->getDim(), aux, 10);
	strcat(buff, aux);
	strcat(buff, "|");
	_itoa(this->dimensiune, aux, 10);
	strcat(buff, aux);
	strcat(buff, "|");
	_itoa(this->abonament->getValoare(), aux, 10);
	strcat(buff, aux);
	strcat(buff, "|");

	return buff;
}

int CUser::verificaExistenta(char* p)
{
	int aux = 0;
	while (aux < this->folder.size() - 1)
	{
		if (strcmp(p, folder.at(aux)->numeFolder()) == 0)
			return 1;
		aux++;
	}
	return 0;
}

int CUser::creareFolder(char* p)
{
	if (this->folder.size() == 0 || verificaExistenta(p) == 0)
	{
		CFolder* fo = new CFolder(p);
		folder.push_back(fo);
		FILE* foo = fopen(p, "w+");
		fclose(foo);
		strcat(p, "*");
		this->dm->adaugareDocument(p);
		char a[256];
		strcpy(a, this->nume.c_str());
		strcat(a, "_Folder.txt");
		
		ofstream f(a, ios::app);
		f << p;
		f << endl;
		f.close();

		return 0;
	}
	else
		return 1;

}

int CUser::mutaDoc(int i, char* b)
{
	int aux = folder.size();
	for(int j =0; j<aux; j++)
		if (strcmp(b, folder.at(j)->numeFolder()) == 0)
		{
			char a[256];
			strcpy(a, dm->veziNume(i));
			int a1 = folder.at(j)->adaugareDocument(a);
			int a2 = dm->stergeDocument(a, i);
			return 0;
		}
	return 1;
}

void CUser::updateAbonament()
{
	char buff[256];
	this->abonament->updateAbonament("Premium", 10000, 200);
	ifstream f("Detalii.txt");
	ofstream g("auxiliar.txt", ios::app);
	while (f.getline(buff, 256))
	{
		char* p = strtok(buff, " \n");
		if (strcmp(p, this->nume.c_str()) != 0)
		{
			g << buff;
			g << endl;
		}
	}
	g << this->nume.c_str() << " " << "Premium" << " " << "10000" << " " << "200" << endl;
	g.close();
	f.close();
	

	FILE* g1 = fopen("auxiliar.txt", "r");
	FILE* f1 = fopen("Detalii.txt", "w");
	while (fgets(buff, 256, g1))
	{
		fprintf(f1, "%s", buff);
	}

	fclose(f1);
	fclose(g1);

	remove("auxiliar.txt");
}