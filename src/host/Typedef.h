#ifndef TYPEDEF_H
#define TYPEDEF_H

#include <string>
#include <cstdio>
#include <iostream>
#include <fstream>

//This is only for CRITICAL runtime errors that CANNOT be handled elegantly.
#define SHARC_KILL_ASSERT(my_message) {std::cout << "SHARC_KILL_ASSERT called from file " << __FILE__ << ", line " <<  __LINE__ << std::endl; std::cout << my_message << std::endl; abort();}

typedef unsigned char ubyte;
typedef unsigned short uint16;

#ifndef GEOM_PRECISION
#define GEOM_PRECISION 1
#endif

#if(GEOM_PRECISION==2)
typedef double g_real;
#else
typedef float g_real;
#endif

typedef unsigned short uint16;

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
    int sky_color, floor_color;
    float cam_x, cam_y, cam_z;
    float cam_elev, cam_rot, zoom_aspect;
    void Defaults(void)
    {
        width = 1920;
        height = 1080;
        cam_x = 0;
        cam_y = 0;
        cam_z = 0;
        cam_elev = 0;
        cam_rot = 0;
        zoom_aspect = 1.7;
        floor_color = 0x00a21273;
        sky_color = 0x00dddddd;
    }

    bool fileexists(std::string name)
    {
        std::ifstream f(name.c_str());
        return f.good();
    }

    void Pack(FILE* fh)
    {
        fwrite(&(width),         sizeof(int),    1, fh);
        fwrite(&(height),        sizeof(int),    1, fh);
        fwrite(&(cam_x),         sizeof(float),  1, fh);
        fwrite(&(cam_y),         sizeof(float),  1, fh);
        fwrite(&(cam_z),         sizeof(float),  1, fh);
        fwrite(&(cam_elev),      sizeof(float),  1, fh);
        fwrite(&(cam_rot),       sizeof(float),  1, fh);
        fwrite(&(zoom_aspect),   sizeof(float),  1, fh);
        fwrite(&(floor_color),   sizeof(int),    1, fh);
        fwrite(&(sky_color),     sizeof(int),    1, fh);
    }

    void Unpack(FILE* fh)
    {
        Defaults();
        fread(&(width),          sizeof(int),    1, fh);
        fread(&(height),         sizeof(int),    1, fh);
        fread(&(cam_x),          sizeof(float),  1, fh);
        fread(&(cam_y),          sizeof(float),  1, fh);
        fread(&(cam_z),          sizeof(float),  1, fh);
        fread(&(cam_elev),       sizeof(float),  1, fh);
        fread(&(cam_rot),        sizeof(float),  1, fh);
        fread(&(zoom_aspect),    sizeof(float),  1, fh);
        fread(&(floor_color),    sizeof(int),    1, fh);
        fread(&(sky_color),      sizeof(int),    1, fh);
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
