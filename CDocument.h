#pragma once
#include "IDocument.h"
class CDocument :
    public IDocument
{
private:
    char nume[32];
    int dimensiune;
    int link = 1000;

public:
    CDocument(char*, int);
    void setNume(char*);
    void setDimensiune(int);
    void setLink();
    char* getNume();
    int getDimensiune();
    int getLink();

};

