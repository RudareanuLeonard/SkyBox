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


void write_file(int client_sock, char *file_name){

    std::cout <<"\n im am write_file method\n";

    std::string file_name_string = file_name;

    std::cout << "file name string = " << file_name_string << "\n";
    
    std::string base_dir = "./files_from_client/";
    std::string relative_path = file_name;
    std::string full_path = base_dir + relative_path;

    // std::experimental::filesystem::create_directory(
    //     std::experimental::filesystem::path(full_path).parent_path()
    // );
        std::filesystem::create_directories(std::filesystem::path(full_path).parent_path());

    

    std::ofstream ofstream_file(full_path, std::ofstream::binary);
    char buffer[1024] = {0};

    if (!ofstream_file.is_open()) {
        std::cout << "Failed to open file\n";

    }

    memset(buffer, 0, sizeof(buffer)); // free buffer before loop
    
    while(true){
        int n = recv(client_sock, buffer, sizeof(buffer), 0);
        if(n <= 0){
            std::cout << "No more recv \n";
            break;
        }
        else{
            std::cout << "\n\n recv received;;;;; buffer = " << buffer << "\n";
            ofstream_file.write(buffer, n);
        }


    }

    ofstream_file.flush();
    ofstream_file.close();

}


void Server::start_server(){
    
    int sockfd = socket(this->server_addrinfo.ai_family, this->server_addrinfo.ai_socktype, this->server_addrinfo.ai_protocol);

    int check_bind = bind(sockfd, (struct sockaddr *)&server_sockaddr_in, sizeof(server_sockaddr_in));

    if(check_bind < 0){
        // std::cout << "Bind failed!\n";
        std::exit(0);
    }

    int check_listen = listen(sockfd, BACKLOG);

    if(check_listen < 0){
        // std::cout << "Listen failed!\n";
        std::exit(0);
    }

    std::cout << "client_sockaddr_in.sin_addr.s_addr = " << this->server_sockaddr_in.sin_addr.s_addr << "\n";



    while(1){
        std::cout <<"\n\n im in while \n\n";
        int client_sock = accept(sockfd, nullptr, nullptr);
        if(client_sock < 0)
            std::cout << "client_sock (accepting connection) FAILED\n";
        else{

            char file_name[1024] = {0};
            std::string file_name_received_string;
            int file_name_received = recv(client_sock, file_name, 1024, 0);
            if(file_name_received <= 0){
                std::cout << "file name received failed\n";
            }
            else{
                // std::string file_name_received_string (file_name, file_name_received);
                file_name[file_name_received] = '\0';
                std::cout << "file_name = " << file_name << "\n";
            }
            
            
            char buffer[1024] = {0};
            memset(buffer, 0, sizeof(buffer));
            std::cout <<"accepting connection is OK\n";
            // recv(client_sock, buffer, sizeof(buffer), 0);

            std::cout << "file_name_received = " << file_name_received << "\n";
            std::cout << "file_name_received_string = " << file_name_received_string << "\n\n";

            write_file(client_sock, file_name);
            // std::cout << "Message from client = " << buffer << "\n";
        }

        // std::thread t_acc_conn(&Server::handle_connection, this, sockfd);
        // std::cout << "Before thread join";
        // t_acc_conn.detach(); // threads run independetly
        // std::cout << "After thread join";
    }

}


int main(void){
    std::cout << "Hello, there is Server.cpp file. I am gonna start a server...\n\n";

    Server server;

    server.start_server();

    std::cout << "Server closed!";
}