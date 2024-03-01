#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>


int main(){
	struct addrinfo hints, *res;
	int fd, sockfd, bfd, acpt;
	struct sockaddr newConnection;

	socklen_t acSpace = INET6_ADDRSTRLEN;
	char ip[acSpace];

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;
	
	fd = getaddrinfo(NULL, "8080", &hints, &res);
	if (fd == -1){
		fprintf(stderr, "Error: %s", gai_strerror(fd));
		return 1;
	
	}	

	if ((sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol)) == -1){
		perror("Socket");
		exit(1);
	}


	int binder = bind(sockfd, res->ai_addr, res->ai_addrlen);
	if (binder == -1){
		perror("bind");
		exit(1);
	}		
	freeaddrinfo(res);
	if ((bfd = listen(sockfd, 10)) == -1){
		perror("listen");
		exit(1);
	}
	if ((acpt = accept(sockfd, &newConnection, &acSpace)) == -1){
	       perror("accept");
		exit(1);
	}
	else{
		printf("accept connection from %s\n", inet_ntop(AF_INET, &(newConnection.sa_data),ip, acSpace ));	
	}
		return 0;
}

