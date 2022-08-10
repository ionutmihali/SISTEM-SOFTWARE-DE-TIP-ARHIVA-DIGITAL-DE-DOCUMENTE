#pragma once
class IFolder
{
    virtual void agaugareNume(char*) = 0;
    virtual int adaugareDocument(char*, char*) = 0;
    virtual int adaugareDocument(char*) = 0;
    virtual char* veziDocument(int i) = 0;
    virtual char* veziNume(int i) = 0;
    virtual int stergeDocument(char* a, int) = 0;
    virtual void reincarcareDate(char*) = 0;
};

