#include "Config.h"
#include "Crc32.h"
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <vector>
#include <string>
#define STL_HDR_SIZE 80
namespace sharc
{
    class StlGeom : public IIoObject
    {
        public:
            StlGeom(void);
            ~StlGeom(void);
            void ReadFromFile(std::string filename);
            void WriteToFile(std::string filename);
            void SavePointCloud(std::string filename);
            int facetCount;
            char header[STL_HDR_SIZE];
            float xmin;
            float xmax;
            float ymin;
            float ymax;
            float zmin;
            float zmax;

        private:
            bool require_free;
            bool fileexists(std::string name);
            void allocate(int num);
            bool machine_big_endian;
            float* normaldata;
            float* vertexdata;
    };
}
