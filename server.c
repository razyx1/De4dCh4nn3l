#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>

int main(){
    //Server socket initialization
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

    char valid_users[][64] = { //array of valid registered usernames
        "razyx",
        "mixxa"
    };

    //accept connection and auth the user
    int client_socket = accept(server_socket, NULL, NULL); //accept connection
    char username[256]; //reserve variable to store received username value from client input
    char userString[] = "Username: "; //template string, made for easier dynamic size allocation for send() function
    send(client_socket, userString, sizeof(userString), 0); //Send the string mentioned above, the client receives "Username: "
    recv(client_socket, username, sizeof(username), 0); //After the client input, the server receives the username value and stores it in the reserve variable

    if(username) { //checks if the user typed something or left the input blank
        int true_flag = 0; //flag to determine wheter the username is valid
        for(int i = 0; i < sizeof(valid_users) || true_flag != 0; i++) { //iterates through the array and sets the flag to 1 if the username exists
            if(username == valid_users[i]) true_flag = 1;
        }
        switch(true_flag){
            case 0: //Flag hasn't changed, refuse connection
                printf("\nFuck off feds\n");
                return 0;
            case 1: //Username was found and the connection may proceed
                break;
        }
    } else { //No input from client side, refuse connection
        printf("\nFuck off feds\n");
        return 0;
    }

    return 0;
}