#include "File.h"

File::File(std::filesystem::directory_entry path, uintmax_t file_size, std::filesystem::file_time_type file_last_write_time){
            std::cout << "This is my file constructor\n";
            this->path = path;
            this->file_size = file_size;
            this->file_last_write_time = file_last_write_time;
}