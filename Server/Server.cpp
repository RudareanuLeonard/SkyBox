#include "Server.h"

Server::Server(){
    std::cout << "This is my Server class constructor\n";
    server_sockaddr_in.sin_family = AF_INET;
    server_sockaddr_in.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_sockaddr_in.sin_port = PORT;

    server_addrinfo.ai_family = AF_INET;
    server_addrinfo.ai_socktype = SOCK_STREAM;
    server_addrinfo.ai_protocol = 0; // 0 = any
    server_addrinfo.ai_addrlen = 4; //length in bytes
    server_addrinfo.ai_addr = (struct sockaddr *)&server_sockaddr_in;
}

void Server::start_server(){
    
    int sockfd = socket(this->server_addrinfo.ai_family, this->server_addrinfo.ai_socktype, this->server_addrinfo.ai_protocol);

    int check_bind = bind(sockfd, (struct sockaddr *)&server_sockaddr_in, 4);

    if(check_bind < 0){
        std::cout << "Bind failed!\n";
        std::exit(0);
    }

    int check_listen = listen(sockfd, BACKLOG);

    if(check_listen < 0){
        std::cout << "Listen failed!\n";
        std::exit(0);
    }

    int client_sock = accept(sockfd, nullptr, nullptr);
}

int main(void){
    std::cout << "Hello, there is Server.cpp file. I am gonna start a server...\n\n";

    Server server;

    server.start_server();
}