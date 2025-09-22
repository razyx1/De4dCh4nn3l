#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
# include <netinet/in.h>


struct userData{
    char username[256];
    char password[256];
};


int main() {

    int server_socket = socket(AF_INET, SOCK_STREAM, 0);   // Server socket initialization
    struct sockaddr_in server_address; // Server address definition
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(9002);
    server_address.sin_addr.s_addr = INADDR_ANY;

    // Binding the socket to IP and port
    bind(server_socket, (struct sockaddr*) &server_address, sizeof(server_address));

    // Listener
    listen(server_socket, 3);

    struct userData users[] = {
        {"mixxa", "m"},
        {"razyx", "r"}
    };
    int numUsers = sizeof(users) / sizeof(users[0]);
    int client_socket = accept(server_socket, NULL, NULL); //Accept connection

    // Asking for username
    char usernamePrompt[] = "Username: ";
    send(client_socket, usernamePrompt, sizeof(usernamePrompt), 0);
    char username[256] = {0};
    recv(client_socket, username, sizeof(username), 0);
    username[strcspn(username, "\r\n")] = 0;
    // Asking for password
    char passwordPrompt[] = "Password: ";
    send(client_socket, passwordPrompt, sizeof(passwordPrompt), 0);
    char password[256] = {0};
    recv(client_socket, password, sizeof(password), 0);
    password[strcspn(password, "\r\n")] = 0;
    // Authentication
    int authenticated = 0;
    for(int i = 0; i < numUsers; i++) {
        if (strcmp(username, users[i].username) == 0 && strcmp(password, users[i].password) == 0) {
          authenticated = 1;
          break;  
        }
    }

    // If statement
    if(authenticated == 1) {
        printf("User %s authenticated!\n", username);
        char successMsg[] = "Login successful!\n";
        send(client_socket, successMsg, sizeof(successMsg), 0);
    } else {
        printf("Invalid login attempt!\n");
        char failMsg[] = "Invalid username or password!\n";
        send(client_socket, failMsg, sizeof(failMsg), 0);
    }

    return 0;
}