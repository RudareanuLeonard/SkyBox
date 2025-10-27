#include "Client.h"
#include <chrono>

Client::Client(){
    std::cout << "This is my Client class constructor\n";
    client_sockaddr_in.sin_family = AF_INET;
    client_sockaddr_in.sin_addr.s_addr = INADDR_ANY;
    client_sockaddr_in.sin_port = htons(PORT); 

    client_addrinfo.ai_family = AF_INET;
    client_addrinfo.ai_socktype = SOCK_STREAM;
    client_addrinfo.ai_protocol = 0;
    client_addrinfo.ai_addrlen = 4;
    client_addrinfo.ai_addr = (struct sockaddr*)&client_sockaddr_in;
}


sockaddr* Server::get_ai_addr(){
    return this->server_addrinfo.ai_addr;
}


Server::Server(){
    std::cout << "This is my Server class constructor\n";
    server_sockaddr_in.sin_family = AF_INET;
    server_sockaddr_in.sin_addr.s_addr = INADDR_ANY;
    server_sockaddr_in.sin_port = htons(PORT);

    server_addrinfo.ai_family = AF_INET;
    server_addrinfo.ai_socktype = SOCK_STREAM;
    server_addrinfo.ai_protocol = 0; // 0 = any
    server_addrinfo.ai_addrlen = 4; //length in bytes
    server_addrinfo.ai_addr = (struct sockaddr *)&server_sockaddr_in;
}


void Client::transfer_file(File file, int sockfd) {
    std::cout << "\n\n THIS IS TRANSFER_FILE \n\n";
    std::ifstream input_file(file.get_path().path(), std::ios::binary);

    if (!input_file.is_open()) {
        std::cout << "Failed to open file\n";
    }

    char buffer[BUFFER_SIZE];
    while (input_file.read(buffer, sizeof(buffer)) || input_file.gcount() > 0) {
        int bytes_sent = send(sockfd, buffer, input_file.gcount(), 0);
        if (bytes_sent < 0) {
            std::cout << "send failed\n";
            break;
        }
        else{
            std::cout << "file sent succesfuly; buffer = " << buffer << "\n";
        }
    }
}

void Client::send_filename(File file, int sockfd, std::string file_name){
    std::cout << "send_file function; file_name = " << file_name << "\n";

    if(send(sockfd, file_name.c_str(), file_name.length(), 0) < 0){
        std::cout << "filename sent failed\n";
    }
    else{
        std::cout << "filename sent succesfully;;;; << " << file_name.c_str() <<"\n";
    }
}


void Client::connect_to_server(Server server){ //TO DO: add file boundaries (length of each file so you know when to create another file)

    FilesManager files_manager;
    std::string path = "test";

    files_manager.lookIntoFolder(path);

    int sockfd;
    const addrinfo *const_client_addrinfo = &(this->client_addrinfo);
    addrinfo *res;
    int client_getaddrinfo = getaddrinfo(INADDR_ANY, "8080", const_client_addrinfo, &res);

    for(auto i: files_manager.get_files_vector()){
         for(addrinfo* p = res; p != NULL; p = p->ai_next){
            sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
            if(sockfd < 0)
                std::cout << "sockfd failed\n";
            
            int client_connect = connect(sockfd, p->ai_addr, p->ai_addrlen);
            if(client_connect < 0)
                std::cout << "client_connect failed\n";

            std::cout <<"i = " << i.get_path().path().string().length() << "\n\n";

            int name_len = i.get_path().path().string().length();
            
            send(sockfd, &name_len, sizeof(name_len), 0);
            this->send_filename(i, sockfd, i.get_path().path().string());
            this->transfer_file(i, sockfd);

         }
    }



    // for(addrinfo* p = res; p != NULL; p = p->ai_next){
    //     sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
    //     if(sockfd < 0)
    //         std::cout << "sockfd failed\n";

    //     int client_connect = connect(sockfd, p->ai_addr, p->ai_addrlen);
    //     if(client_connect < 0)
    //         std::cout << "client_connect failed\n";


        
    //     // char *message = "TEST MESSAGE";
    //     // char *message;
    //     // std::cin.getline(message, BUFFER_SIZE);

    //     for(auto i: files_manager.get_files_vector()){
    //         std::cout << "for\n";
    //         std::cout << "i = " << i.get_path() << "\n\n";
    //         this->send_filename(i, sockfd, i.get_path().path().string()); // i.get_path().path().string()i.get_path().path().string() + "\0")
    //         this->transfer_file(i, sockfd);
    //     }


    //     // send(sockfd, message, sizeof(message), 0);
        

    //     // if(message == "4")
    //     //     close(sockfd);
    // }

}

int main(void){
    
    Server server;
    
    // auto start = std::chrono::high_resolution_clock::now();

    Client client;
    client.connect_to_server(server);
    
}