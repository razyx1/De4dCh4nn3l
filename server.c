#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>

int main(){
    char server_message[256] = "SERVER REACHED";

    int server_socket;
    server_socket = socket(AF_INET, SOCK_STREAM, 0);

    //Server address definition
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(9002);
    server_address.sin_addr.s_addr = INADDR_ANY;

    //Bind the socket to IP and port
    bind(server_socket, (struct sockaddr*) &server_address, sizeof(server_address));

    //Listener
    listen(server_socket, 3);

    int client_socket = accept(server_socket, NULL, NULL);

    send(client_socket, server_message, sizeof(server_message), 0);

    close(server_socket);

    return 0;
}