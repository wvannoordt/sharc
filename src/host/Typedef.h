#ifndef TYPEDEF_H
#define TYPEDEF_H

#include <string>
#include <cstdio>

typedef unsigned char ubyte;

struct IIoObject
{
    virtual void ReadFromFile(std::string filename)=0;
    virtual void WriteToFile(std::string filename)=0;
};

struct IPackable
{
    virtual void Pack(FILE* fh)=0;
    virtual void Unpack(FILE* fh)=0;
};

#endif
