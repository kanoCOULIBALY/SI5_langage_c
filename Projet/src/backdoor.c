#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h> 
#include <signal.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int sock_fd = 0;
int client_sock_fd = 0;
static const int PORT = 2222;

void shutdown_server(int signal_num) {
    if (signal_num == SIGINT) {
        if (client_sock_fd != 0)
            close(client_sock_fd);
        if (sock_fd != 0)
            close(sock_fd);
        exit(0);
    }
}

int main(int argc, char **argv) {
    struct sockaddr_in addr, cli_addr;
    socklen_t cli_len = sizeof(cli_addr);
    char buffer[64];
    
    signal(SIGINT, shutdown_server);
    
    sock_fd = socket(AF_INET, SOCK_STREAM, 0);

    memset(&addr, 0, sizeof(addr));
    
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(PORT);
    
    bind(sock_fd, (struct sockaddr *) &addr, sizeof(addr));

    listen(sock_fd, 1);

    while (1) {
        memset(&cli_addr, 0, sizeof(cli_addr));
        memset(&buffer, 0, 64);
        client_sock_fd = 0;
        
        client_sock_fd = accept(sock_fd, (struct sockaddr *) &cli_addr, &cli_len);
        
        if (client_sock_fd > 1) {

            write(client_sock_fd, buffer, strlen(buffer));
            
            close(client_sock_fd);
        }
    }
    
    return 0;
}
