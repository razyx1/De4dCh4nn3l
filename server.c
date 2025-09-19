#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>

int main(){
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

    char valid_users[][64] = {
        "razyx",
        "mixxa"
    };

    int client_socket = accept(server_socket, NULL, NULL);
    char username[256];
    char userString[] = "Username: ";
    send(client_socket, userString, sizeof(userString), 0);
    recv(client_socket, username, sizeof(username), 0);

    if(username) {
        int true_flag = 0;
        for(int i = 0; i < sizeof(valid_users) || true_flag != 0; i++) {
            if(username == valid_users[i]) true_flag = 1;
        }
        switch(true_flag){
            case 0:
                printf("\nFuck off feds\n");
                return 0;
            case 1:
                break;
        }
    } else {
        printf("\nFuck off feds\n");
        return 0;
    }

    return 0;
}