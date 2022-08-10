#pragma once
#include "CDocument.h"
#include "IFolder.h"
#include <vector>
#include <string>
using namespace std;

class CFolder :
    public IFolder
{
private:
    string nume;
    vector<CDocument*> doc;
    int nr_documente;

public:
    CFolder() { this->nume = ""; this->nr_documente = 0; }
    CFolder(string n) { this->nume = n; this->nr_documente = 0; }
    void agaugareNume(char*);
    int adaugareDocument(char*, char*);
    int adaugareDocument(char*);
    char* veziDocument(int i);
    char* veziNume(int i);
    int stergeDocument(char* a, int);
    void reincarcareDate(char*);
    int getNrDoc();
    int verificareExistenta(char*);
    char* numeFolder();
};

