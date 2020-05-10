#ifndef TYPEDEF_H
#define TYPEDEF_H

#include <string>
#include <cstdio>
#include <iostream>
#include <fstream>
#include "CuGLInterop.h"

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

typedef float vec3[3];

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

struct SharcShaderLayers
{
    int* imdata;
    int Ni, Nj;
    g_real* incident_x[3];
    float* incident_n[3];
    uint16* object_id;
};

struct SharcSettings
{
    int width, height;
    int sky_color, floor_color;
    float cam_x, cam_y, cam_z;
    float cam_elev, cam_rot, zoom_aspect;
    float rot_sin, rot_cos, elev_cos, elev_sin;
    bool rdr_floor;
    float floor_height;
    vec3 cam_n;
};

#endif
