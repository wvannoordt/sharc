#include "Config.h"
#include "Crc32.h"
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <vector>
#include "sharc.h"
#include "StlGeom.h"
#include <fstream>
#include <sys/stat.h>
#include <unistd.h>
#include <string>

namespace sharc
{
    bool StlGeom::fileexists(std::string name)
    {
        std::ifstream f(name.c_str());
        return f.good();
    }

    StlGeom::StlGeom(void)
    {
        int num = 1;
        machine_big_endian = !(*(char*)&num==1);
        if (machine_big_endian) SHARC_KILL_ASSERT("Detected big-endian machine: unable to convert from little-endian data for now.\nThis may cause undefined behavior.");
        require_free = false;
        facetCount = -999;
    }

    StlGeom::~StlGeom(void)
    {
        if (require_free)
        {
            free(normaldata);
            free(vertexdata);
        }
    }

    void StlGeom::ReadFile(std::string filename)
    {
        if (!fileexists(filename)) SHARC_KILL_ASSERT("Cannot find file " << filename << ".");
        FILE* file_writer;
        file_writer = fopen(filename.c_str(), "r+b");
        fread(header, sizeof(char), STL_HDR_SIZE, file_writer);
        fread(&facetCount, sizeof(int), 1, file_writer);
        allocate(facetCount);
        float xmin =  1e30;
        float xmax = -1e30;
        float ymin =  1e30;
        float ymax = -1e30;
        float zmin =  1e30;
        float zmax = -1e30;
        char dummy[2];
        for (int i = 0; i < facetCount; i++)
        {
            fread(normaldata+3*i, sizeof(float), 3, file_writer);
            fread(vertexdata+9*i, sizeof(float), 9, file_writer);
            fread(dummy, sizeof(char), 2, file_writer);
            xmax = (vertexdata[9*i+0]>xmax)?vertexdata[9*i+0]:xmax;
            xmax = (vertexdata[9*i+3]>xmax)?vertexdata[9*i+3]:xmax;
            xmax = (vertexdata[9*i+6]>xmax)?vertexdata[9*i+6]:xmax;
            xmin = (vertexdata[9*i+0]<xmin)?vertexdata[9*i+0]:xmin;
            xmin = (vertexdata[9*i+3]<xmin)?vertexdata[9*i+3]:xmin;
            xmin = (vertexdata[9*i+6]<xmin)?vertexdata[9*i+6]:xmin;
            ymax = (vertexdata[9*i+1]>ymax)?vertexdata[9*i+1]:ymax;
            ymax = (vertexdata[9*i+4]>ymax)?vertexdata[9*i+4]:ymax;
            ymax = (vertexdata[9*i+7]>ymax)?vertexdata[9*i+7]:ymax;
            ymin = (vertexdata[9*i+1]<ymin)?vertexdata[9*i+1]:ymin;
            ymin = (vertexdata[9*i+4]<ymin)?vertexdata[9*i+4]:ymin;
            ymin = (vertexdata[9*i+7]<ymin)?vertexdata[9*i+7]:ymin;
            zmax = (vertexdata[9*i+2]>zmax)?vertexdata[9*i+2]:zmax;
            zmax = (vertexdata[9*i+5]>zmax)?vertexdata[9*i+5]:zmax;
            zmax = (vertexdata[9*i+8]>zmax)?vertexdata[9*i+8]:zmax;
            zmin = (vertexdata[9*i+2]<zmin)?vertexdata[9*i+2]:zmin;
            zmin = (vertexdata[9*i+5]<zmin)?vertexdata[9*i+5]:zmin;
            zmin = (vertexdata[9*i+8]<zmin)?vertexdata[9*i+8]:zmin;
        }
        fclose(file_writer);
    }

    void StlGeom::allocate(int num)
    {
        normaldata = (float*)malloc(3*num*sizeof(float));
        vertexdata = (float*)malloc(9*num*sizeof(float));

        require_free = true;
    }
}
