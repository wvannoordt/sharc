#ifndef USER_SETTINGS_HANDLE_H
#define USER_SETTINGS_HANDLE_H
#include "Typedef.h"
namespace sharc
{
    class SharcUserSettingsHandle : public IIoObject, public IPackable
    {
        public:
            SharcUserSettingsHandle(SharcSettings* child_in);
            SharcUserSettingsHandle();
            void Defaults(void);
            void ReadFromFile(std::string filename);
            void WriteToFile(std::string filename);
            void Pack(FILE* fh);
            void Unpack(FILE* fh);
        private:
            bool fileexists(std::string name);
            SharcSettings* child;
    };
}
#endif
