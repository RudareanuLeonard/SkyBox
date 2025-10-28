#include "File.h"
#include <chrono>

File::File(std::filesystem::directory_entry path, uintmax_t file_size, std::filesystem::file_time_type file_last_write_time){
            std::cout << "This is my file constructor\n";
            // std::cout << "Last time file was edited is: " << std::filesystem::last_write_time(this);
            this->path = path;
            // this->file_size = file_size;
            // this->file_last_write_time = file_last_write_time;
}

std::filesystem::directory_entry File::get_path(){
    return this->path;
}

void File::last_write_time(){
    std::filesystem::file_time_type ftime = std::filesystem::last_write_time(this->get_path());
    std::cout << std::format("File write time is {}\n", ftime);
}