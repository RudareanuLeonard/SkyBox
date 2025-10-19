#include "FilesManager.h"
#include <typeinfo>

FilesManager::FilesManager(){
    std::cout << "This is my FilesManager constructor!\n";
}

std::vector<File> FilesManager::get_files_vector(){
    return this->files_vector;
}


void FilesManager::lookIntoFolder(std::string analyzed_folder_path){
    // std::cout << "TEST";
    std::filesystem::path path;
    path = analyzed_folder_path;
    

    std::cout << "path = " << path.relative_path() << "\n";
    
    
    for(const std::filesystem::directory_entry& file : std::filesystem::recursive_directory_iterator(path)){
        if(std::filesystem::is_regular_file(file)){
            
            std::cout << file << "; file size = "<< std::filesystem::file_size(file) << ";;;; and last write time = " << last_write_time_to_string(std::filesystem::last_write_time(file)) <<"\n\n";
            std::cout << "file type = " << typeid(file).name() << " file size type = " << typeid(std::filesystem::file_size(file)).name() << " std::string\n\n";
            std::cout << "qqqqqqqqqqqq = " << file.path() << "\n\n\n\n\n";

            File file_obj(file, std::filesystem::file_size(file), std::filesystem::last_write_time(file));
            
            //also keep in mind to check on permissions - to do that later
            this->add_to_vector(&file_obj);
        }
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

void FilesManager::add_to_vector(File *file){
    this->files_vector.push_back(*file);
}

// int main(void){
//     FilesManager fm;

//     std::string analyzed_folder_path = "test";

//     fm.lookIntoFolder(analyzed_folder_path);
// }