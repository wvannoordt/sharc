#include "Config.h"
#include "Crc32.h"
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <vector>
#include "Typedef.h"

namespace sharc
{
    class PngWriter
    {
        public:
            void write_png(const char* filename_png_ext, const int& width, const int& height, int* imdata);
            PngWriter(void);
        private:
            bool machine_big_endian;
            Crc32 crc32_checksum;
            void write_signature(FILE* file_writer);
            void write_header(FILE* file_writer, const int& width, const int& height);
            void write_data(FILE* file_writer, const int& col, const int& row, int* imdata);
            void write_end(FILE* file_writer);
            void flip_endianness(int* i);
            void compress_memory(void *in_data, size_t in_data_size, std::vector<uint8_t> &out_data);
    };
}
