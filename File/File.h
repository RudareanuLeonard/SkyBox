#include <iostream>
#include <string>
#include <filesystem>

class File{

    private:
        std::filesystem::directory_entry path;
        // std::filesystem::directory_entry file_size;
        uintmax_t file_size;
        std::filesystem::file_time_type file_last_write_time;

    public:
        File(std::filesystem::directory_entry path, uintmax_t file_size, std::filesystem::file_time_type file_last_write_time);

};