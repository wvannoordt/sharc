#ifndef CRC32_H
#define CRC32_H

#include "Config.h"

#define CRC32_TABLE_CT 256

namespace sharc
{
    class Crc32
    {
        public:
            Crc32(void);
            unsigned int compute_checksum(ubyte* bytes, int length);
        private:
            unsigned int table[CRC32_TABLE_CT];
    };

}
#endif
