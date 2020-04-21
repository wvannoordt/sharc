#ifndef TYPEDEF_H
#define TYPEDEF_H

#include <string>
#include <cstdio>
#include <iostream>
#include <fstream>

//This is only for CRITICAL runtime errors that CANNOT be handled elegantly.
#define SHARC_KILL_ASSERT(my_message) {std::cout << "SHARC_KILL_ASSERT called from file " << __FILE__ << ", line " <<  __LINE__ << std::endl; std::cout << my_message << std::endl; abort();}

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

struct SharcSettings : public IIoObject, public IPackable
{
    int width, height;
    void Defaults(void)
    {
        width = 1920;
        height = 1080;
    }

    bool fileexists(std::string name)
    {
        std::ifstream f(name.c_str());
        return f.good();
    }

    void Pack(FILE* fh)
    {
        fwrite(&(width),        sizeof(int),    1, fh);
        fwrite(&(height),       sizeof(int),    1, fh);
    }

    void Unpack(FILE* fh)
    {
        Defaults();
        fread(&(width),          sizeof(int),    1, fh);
        fread(&(height),         sizeof(int),    1, fh);
    }

    void ReadFromFile(std::string filename)
    {
        if (!fileexists(filename)) SHARC_KILL_ASSERT("Cannot find file " << filename << ".");
        FILE* fh;
        fh = fopen(filename.c_str(), "r+b");
        Unpack(fh);
        fclose(fh);
    }

    void WriteToFile(std::string filename)
    {
        FILE* fh;
        fh = fopen(filename.c_str(), "w+b");
        Pack(fh);
        fclose(fh);
    }
};

#endif
