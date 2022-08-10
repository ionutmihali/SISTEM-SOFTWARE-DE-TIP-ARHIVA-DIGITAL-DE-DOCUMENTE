#pragma once
class IDocument
{
    virtual void setNume(char*) = 0;
    virtual void setDimensiune(int) = 0;
    virtual void setLink() = 0;
    virtual char* getNume() = 0;
    virtual int getDimensiune() = 0;
    virtual int getLink() = 0;
};

