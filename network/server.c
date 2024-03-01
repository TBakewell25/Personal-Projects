#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>
 
#define PORT "3490"
#define BACKLOG 10
void *get_in_addr(struct sockaddr* sa){
        if (sa->sa_family == AF_INET){
                return &(((struct sockaddr_in*)sa)->sin_addr);
}
        return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

int main(void){
        int sockfd, new_fd;
        struct addrinfo hints, *serverinfo, *p;
        struct sockaddr_storage their_addr;
        socklen_t sin_size;
        struct sigaction sa;
        int yes=1;
        
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_family = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;
	
	int rv = getaddrinfo(NULL, PORT, &hints, &serverinfo);

	if (rv != 0){
		printf("test");
		perror("getaddrinfo");
	}
	for (p=serverinfo; p != NULL; p = p->ai_next){
		if(sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol) != 0){
			printf("test");
			perror("Socket");
		}

		if (bind(rv, p->ai_addr, p->ai_addrlen) != 0){
			perror("Bind");
		}

	}
	listen(sockfd, BACKLOG);
	while(1){
		sin_size = sizeof their_addr;
		if(accept(sockfd, (struct sockaddr*)&their_addr, &sin_size)== -1){
				perror("accept");
				}

		send(new_fd, "Hello world!", 13, 0);
	}
	}
