#pragma once
#include <string>
using namespace std;

class CAbonament 
{
private:
	string nume;
	int max;
	int valoare;
public:
	CAbonament() {
		this->nume = "Standard"; 
		this->max = 200;
		this->valoare = 0;
	}
	string getNume()
	{
		return this->nume;
	}
	int getDim()
	{
		return this->max;
	}
	int getValoare()
	{
		return this->valoare;
	}

	void updateAbonament(string n, int m, int v)
	{
		this->nume = n;
		this->max = m;
		this->valoare = v;
	}
};

