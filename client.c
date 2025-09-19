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
        printf("FATAL ERROR, FAILED TO CONNECT TO SERVER. RETRYING...\n");
        if(i == 0) {
            printf("FATAL ERROR, RETRIES EXTINGUISHED.\n");
            return 1;
        }
    }

    printf("Connection to DedSec servers established.\n");

    //send username and password for auth check
    char server_response[256]; //Get server requests
    recv(network_socket, &server_response, sizeof(server_response), 0); // Same here
    printf("%s", server_response); //Print the request
    char username[256]; //Variable for input
    scanf("%s", &username);
    send(network_socket, username, sizeof(username), 0); //Send the variable for auth check

    return 0;
}