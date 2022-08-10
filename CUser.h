#pragma once
#include "CFolderUser.h"
#include "CFolderFavorite.h"
#include "CFolderCos.h"
#include "CAbonament.h"
#include <string>
#include <vector>
using namespace std;

class CUser
{
private:
	string nume;
	string parola;
	CAbonament* abonament;
	int dimensiune;
	CFolderUser* dm;
	CFolderFavorite* df;
	CFolderCos* cos;
	vector<CFolder*> folder;

public:
	CUser(string a, string b);
	void setNume(char n[]);
	void setParola(char p[]);
	void setAbonament();
	char* getDocMele();
	char* getDocPref();
	char* getDocCos();
	char* detaliiCont();
	void creareFoldereInitiale();
	int adaugareDocument(char*, char*);
	char* veziDocument(int i);
	int favDocument(int i);
	int unfavDocument(int i);
	int cosDocumentMele(int i);
	void reincarcareDate();
	int recoverDocument(int i);
	int stergeDocument(int i);
	void golesteCos();
	void incarcareDetalii();
	int verificaExistenta(char* p);
	int creareFolder(char*);
	int mutaDoc(int i, char* b);
	void updateAbonament();
};

