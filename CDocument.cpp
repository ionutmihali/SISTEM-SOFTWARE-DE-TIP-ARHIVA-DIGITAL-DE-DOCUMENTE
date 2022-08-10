#define _CRT_SECURE_NO_WARNINGS
#include "CDocument.h"
#include "string.h"
using namespace std;

CDocument::CDocument(char* n, int d)
{
	this->dimensiune = d;
	strcpy(this->nume, n);
	this->link = this->link + 111;
}

void CDocument::setNume(char* n)
{
	strcpy(this->nume, n);
}

void CDocument::setDimensiune(int d)
{
	this->dimensiune = d;
}

void CDocument::setLink()
{
	this->link = this->link + 111;
}

char* CDocument::getNume()
{
	return this->nume;
}

int CDocument::getDimensiune()
{
	return this->dimensiune;
}

int CDocument::getLink()
{
	return this->link;
}