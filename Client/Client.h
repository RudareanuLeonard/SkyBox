#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

const int PORT = 8080;

class Client{
    private:
        addrinfo client_addrinfo = addrinfo(); // we declare it here because addrinfo is a PODT
        sockaddr_in client_sockaddr_in; // we declare it sockaddr and not sockaddr_in (specific for ipv4) in order to pass it to server_addrinfo (addrinfo has a field of type sockaddr)


    public:
        Client();

        void connect_to_server();
};