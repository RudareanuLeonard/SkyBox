#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

const std::string LOCALHOST = "127.0.0.1";
const int PORT = 8080;
const int BACKLOG = 5;

//addrinfo
//sockaddr_in <- for IPv4

class Server{
    private:
    addrinfo server_addrinfo = addrinfo(); // we declare it here because addrinfo is a PODT
    sockaddr_in server_sockaddr_in; // we declare it sockaddr and not sockaddr_in (specific for ipv4) in order to pass it to server_addrinfo (addrinfo has a field of type sockaddr)


    public:
    Server();
    void start_server();

};