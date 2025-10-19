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


void Client::transfer_file(File file, int sockfd){
    std::filesystem::directory_entry file_path = file.get_path();

    std::ifstream input_file(file_path.path());
    std::string line;

    char buffer[BUFFER_SIZE] = {0};

    while(std::getline(input_file, line)){
        if(send(sockfd, line.c_str(), line.size(), 0) < 0){
            std::cout << "line = " << line << " SEND FAILED !\n\n";
        }


    }
}



void Client::connect_to_server(Server server){
    
    int sockfd;
    const addrinfo *const_client_addrinfo = &(this->client_addrinfo);
    addrinfo *res;
    int client_getaddrinfo = getaddrinfo(INADDR_ANY, "8080", const_client_addrinfo, &res);

    for(addrinfo* p = res; p != NULL; p = p->ai_next){
        sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
        if(sockfd < 0)
            std::cout << "sockfd failed\n";

        int client_connect = connect(sockfd, p->ai_addr, p->ai_addrlen);
        if(client_connect < 0)
            std::cout << "client_connect failed\n";
        
        char *message = "TEST MESSAGE";
        // char *message;
        // std::cin.getline(message, BUFFER_SIZE);
        send(sockfd, message, sizeof(message), 0);
        

        // if(message == "4")
        //     close(sockfd);
    }

}

int main(void){
    
    Server server;
    
    // auto start = std::chrono::high_resolution_clock::now();

    Client client;
    client.connect_to_server(server);
    
}