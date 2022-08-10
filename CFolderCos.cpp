#include "CFolderCos.h"

void CFolderCos::golesteCos()
{
	int i = this->getNrDoc();
	while (i > 0)
	{
		char* a = this->veziNume(i);
		this->stergeDocument(a, i);
		i--;
	}
}