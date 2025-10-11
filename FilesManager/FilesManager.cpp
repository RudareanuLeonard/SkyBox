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
        std::cout << file << "\n";
    }


}

int main(void){
    FilesManager fm;

    std::string analyzed_folder_path = "test";

    fm.lookIntoFolder(analyzed_folder_path);
}