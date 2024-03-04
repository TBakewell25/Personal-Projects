#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <netdb.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[]){
	struct addrinfo hints, *res, con;
	int addr, sockfd, accept, rec;

	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	
	char* port = argv[2];

	if ((addr =getaddrinfo(argv[1], port, &hints, &res)) == -1){
		fprintf(stderr, "Error: %s", gai_strerror(addr));
		exit(1);
	}

	if ((sockfd = socket(res->ai_family, res->ai_socktype, 0)) == -1){
		printf("Error: %s", strerror(errno));
		exit(1);
	}

	if ((accept = connect(sockfd, res->ai_addr, res->ai_addrlen)) == -1){
		printf("Error: %s", strerror(errno));
		exit(1);
	}

	while(1){
		fd_set reads;
		FD_ZERO(&reads);
		FD_SET(sockfd, &reads);
		FD_SET(0, &reads);

		struct timeval timeout;
		timeout.tv_sec = 0;
		timeout.tv_sec = 100000;

		if (select(sockfd+1, &reads,0,0,&timeout)<0){
			fprintf(stderr, "Error: %s", strerror(errno));
			exit(1);
		}

		if (FD_ISSET(sockfd, &reads)){
			char read[4096];
			int bytes_received = recv(sockfd, read, 4096, 0);
			if (bytes_received < 1){
				printf("Connection closed\n");
				break;
			}
			printf("Received (%d Bytes): %.*s\n", bytes_received, bytes_received, read);
		}

		if(FD_ISSET(0, &reads)){
				char read[4096];
				if (!fgets(read, 4096, stdin)) break;
				printf("Sending: %s", read);
				int bytes_sent = send(sockfd, read, strlen(read), 0);
				printf("Sent %d bytes.\n", bytes_sent);
				}
	}

	close(sockfd);

//	if ((rec = recv(sockfd, buffer, sizeof buffer, 0)) == -1){
//		printf("Error: %s", strerror(errno));
//		exit(1);
//	}

//	printf("%s\n", buffer);
	return 0;
}
