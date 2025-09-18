#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(){
    int network_socket;
    network_socket = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(9002);
    server_address.sin_addr.s_addr = INADDR_ANY;

    int connection = connect(network_socket, (struct sockaddr *) &server_address, sizeof(server_address));
    for(int i = 3; connection == -1; i--) {
        printf("FATAL ERROR, THE SERVER FAILED TO FIRE UP.\nRETRYING...");
        if(i == 0) {
            printf("FATAL ERROR, RETRIES EXTINGUISHED.");
            return 1;
        }
    }

    char server_response[256];
    recv(network_socket, &server_response, sizeof(server_response), 0);

    if(connection != -1) {
        printf("**..SERVER FIRED UP..**\n");
        printf("SERVER DATA: %s\n", server_response);
        printf("HAPPY HACKING!\n");
    }

    close(network_socket);

    return 0;
}