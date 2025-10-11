#include "FilesManager.h"

FilesManager::FilesManager(){
    std::cout << "This is my FilesManager constructor!\n";
}

void FilesManager::lookIntoFolder(std::string analyzed_folder_path){
    // std::cout << "TEST";
    std::filesystem::path path;
    path = analyzed_folder_path;

    std::cout << "path = " << path.relative_path() << "\n";

    for(const auto& file : std::filesystem::recursive_directory_iterator(path)){
        if(std::filesystem::is_regular_file(file))
            std::cout << file << "; file size = "<< std::filesystem::file_size(file) << ";;;; and last write time = " << last_write_time_to_string(std::filesystem::last_write_time(file))
<<"\n";
        //create map; also keep in mind to check on permissions - to do that later
    }
}

std::string FilesManager::last_write_time_to_string(const std::filesystem::file_time_type& ftime){
    return std::format("{:%c}", ftime);
}

// void FilesManager::createMap(const auto& file){
//     if(map.find(file) == map.end()){
//         std::cout << "Key is not in the map. Adding it...\n";
//     }
// }


int main(void){
    FilesManager fm;

    std::string analyzed_folder_path = "test";

    fm.lookIntoFolder(analyzed_folder_path);
}