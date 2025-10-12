#include <iostream>
#include <string>
#include <filesystem>
#include <format>
#include <chrono>
#include <ctime>
#include <vector>
#include "../File/File.h"

class FilesManager{

    private:
        std::vector<File> files_vector;

    public:
    FilesManager();

    void lookIntoFolder(std::string analyzed_folder_path);

    void createMap(const auto& file); // here i'll create the map to get file infos (path, size, last_modified_date)

    std::string last_write_time_to_string(const std::filesystem::file_time_type& ftime);

    void add_to_vector(File *file);

};