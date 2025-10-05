#include "Client.h"


Client::Client(){
    std::cout << "This is my Client class constructor\n";
    client_sockaddr_in.sin_family = AF_INET;
    client_sockaddr_in.sin_addr.s_addr = inet_addr("127.0.0.1");
    client_sockaddr_in.sin_port = PORT;

    client_addrinfo.ai_family = AF_INET;
    client_addrinfo.ai_socktype = SOCK_STREAM;
    client_addrinfo.ai_protocol = 0;
    client_addrinfo.ai_addrlen = 4;
    client_addrinfo.ai_addr = (struct sockaddr*)&client_sockaddr_in;
}


void Client::connect_to_server(){

    int sockfd;
    
    const addrinfo *const_client_addrinfo = &(this->client_addrinfo);
    addrinfo *res;

    int client_getaddrinfo = getaddrinfo("127.0.0.1", "8080", const_client_addrinfo, &res);
    // std::cout << "client get addr info = " << client_getaddrinfo << "\n";


    for(addrinfo *p = res; p != NULL; p = p->ai_next){
        int sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
        if(sockfd < 0){
            std::cout << "sockfd failed\n";
        }


        int client_connect = connect(sockfd, p->ai_addr, p->ai_addrlen);

        if(client_connect < 0){
            std::cout << "Client connection failed\n";
            std::cerr << "Client connection failed: " << strerror(errno) << "\n";

        }

        // std::cout << "TEST";
    }

    // int sockfd = socket()

}

int main(void){
    Client client;
    client.connect_to_server();
}