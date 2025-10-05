#include "Client.h"


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


void Client::connect_to_server(Server server){

    int sockfd = socket(this->client_addrinfo.ai_family, this->client_addrinfo.ai_socktype, this->client_addrinfo.ai_protocol);
    std::cout << "this->client_addrinfo.ai_family = " << this->client_addrinfo.ai_family << "    this->client_addrinfo.ai_socktype = " << this->client_addrinfo.ai_socktype << "   this->client_addrinfo.ai_protocol = " << this->client_addrinfo.ai_protocol << "\n";

    sockaddr* server_addr = server.get_ai_addr();

    if(connect(sockfd, server_addr, sizeof(server_addr)) < 0)
        std::cerr << "Client connection failed: " << strerror(errno) << "\n";
    else
        std::cout << "connection successful";


    // int sockfd;
    
    // const addrinfo *const_client_addrinfo = &(this->client_addrinfo);
    // addrinfo *res;

    // struct addrinfo hints{};

    // // int client_getaddrinfo = getaddrinfo("127.0.0.1", "8080", &hints, &res);
    // // std::cout << "client get addr info = " << client_getaddrinfo << "\n";
    
    // sockfd = socket(this->client_addrinfo.ai_family, this->client_addrinfo.ai_socktype, this->client_addrinfo.ai_protocol);

    // if(sockfd < 0)
    //     std:: cout << "sockfd failed";

    // int q = connect(sockfd, this->client_addrinfo.ai_addr, this->client_addrinfo.ai_addrlen);

    // if(q < 0)
    //     std::cout << "Q conn failed";

    // if(res != NULL)
    //     std :: cout << "res not null";
    // else
    //     std::cout << "res is null";





    // for(addrinfo *p = res; p != NULL; p = p->ai_next){
    //     int sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
    //     if(sockfd < 0){
    //         std::cout << "sockfd failed\n";
    //     }


    //     int client_connect = connect(sockfd, p->ai_addr, p->ai_addrlen);

    //     if(client_connect < 0){
    //         // std::cout << "Client connection failed\n";
            // std::cerr << "Client connection failed: " << strerror(errno) << "\n";

    //     }

    //     // std::cout << "TEST";
    // }

    // int sockfd = socket()

}

int main(void){
    Client client;
    Server server;
    client.connect_to_server(server);
}