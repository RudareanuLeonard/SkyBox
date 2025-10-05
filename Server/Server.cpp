#include "Server.h"

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

sockaddr* Server::get_ai_addr(){
    return this->server_addrinfo.ai_addr;
}


void Server::start_server(){
    
    int sockfd = socket(this->server_addrinfo.ai_family, this->server_addrinfo.ai_socktype, this->server_addrinfo.ai_protocol);

    int check_bind = bind(sockfd, (struct sockaddr *)&server_sockaddr_in, sizeof(server_sockaddr_in));

    if(check_bind < 0){
        std::cout << "Bind failed!\n";
        std::exit(0);
    }

    int check_listen = listen(sockfd, BACKLOG);

    if(check_listen < 0){
        std::cout << "Listen failed!\n";
        std::exit(0);
    }

    std::cout << "client_sockaddr_in.sin_addr.s_addr = " << this->server_sockaddr_in.sin_addr.s_addr << "\n";

    while(1)
        int client_sock = accept(sockfd, nullptr, nullptr);
}

int main(void){
    std::cout << "Hello, there is Server.cpp file. I am gonna start a server...\n\n";

    Server server;

    server.start_server();

    std::cout << "Server closed!";
}