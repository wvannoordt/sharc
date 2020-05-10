#include "SharcUserSettingsHandle.h"
namespace sharc
{
    SharcUserSettingsHandle::SharcUserSettingsHandle(SharcSettings* child_in)
    {
        child = child_in;
    }

    SharcUserSettingsHandle::SharcUserSettingsHandle()
    {

    }

    void SharcUserSettingsHandle::Defaults(void)
    {
        child->width = 1920;
        child->height = 1080;
        child->cam_x = 0;
        child->cam_y = 0;
        child->cam_z = 0;
        child->cam_elev = 0;
        child->cam_rot = 0;
        child->zoom_aspect = 1.7;
        child->floor_color = 0x00a21273;
        child->sky_color = 0x00dddddd;
        child->rdr_floor = true;
        child->floor_height = -10;
    }

    bool SharcUserSettingsHandle::fileexists(std::string name)
    {
        std::ifstream f(name.c_str());
        return f.good();
    }

    void SharcUserSettingsHandle::ReadFromFile(std::string filename)
    {
        if (!fileexists(filename)) SHARC_KILL_ASSERT("Cannot find file " << filename << ".");
        FILE* fh;
        fh = fopen(filename.c_str(), "r+b");
        Unpack(fh);
        fclose(fh);
    }

    void SharcUserSettingsHandle::WriteToFile(std::string filename)
    {
        FILE* fh;
        fh = fopen(filename.c_str(), "w+b");
        Pack(fh);
        fclose(fh);
    }

    void SharcUserSettingsHandle::Pack(FILE* fh)
    {
        fwrite(&(child->width),         sizeof(int),    1, fh);
        fwrite(&(child->height),        sizeof(int),    1, fh);
        fwrite(&(child->cam_x),         sizeof(float),  1, fh);
        fwrite(&(child->cam_y),         sizeof(float),  1, fh);
        fwrite(&(child->cam_z),         sizeof(float),  1, fh);
        fwrite(&(child->cam_elev),      sizeof(float),  1, fh);
        fwrite(&(child->cam_rot),       sizeof(float),  1, fh);
        fwrite(&(child->zoom_aspect),   sizeof(float),  1, fh);
        fwrite(&(child->floor_color),   sizeof(int),    1, fh);
        fwrite(&(child->sky_color),     sizeof(int),    1, fh);
        fwrite(&(child->rdr_floor),     sizeof(bool),   1, fh);
        fwrite(&(child->floor_height),  sizeof(float),  1, fh);
    }

    void SharcUserSettingsHandle::Unpack(FILE* fh)
    {
        Defaults();
        fread(&(child->width),          sizeof(int),    1, fh);
        fread(&(child->height),         sizeof(int),    1, fh);
        fread(&(child->cam_x),          sizeof(float),  1, fh);
        fread(&(child->cam_y),          sizeof(float),  1, fh);
        fread(&(child->cam_z),          sizeof(float),  1, fh);
        fread(&(child->cam_elev),       sizeof(float),  1, fh);
        fread(&(child->cam_rot),        sizeof(float),  1, fh);
        fread(&(child->zoom_aspect),    sizeof(float),  1, fh);
        fread(&(child->floor_color),    sizeof(int),    1, fh);
        fread(&(child->sky_color),      sizeof(int),    1, fh);
        fread(&(child->rdr_floor),      sizeof(bool),   1, fh);
        fread(&(child->floor_height),   sizeof(float),  1, fh);
    }
}
