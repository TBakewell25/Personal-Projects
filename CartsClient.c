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

	char buffer[20];

	if ((addr =getaddrinfo(argv[1], "8080", &hints, &res)) == -1){
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

	if ((rec = recv(accept, buffer, sizeof buffer, 0)) == -1){
		printf("Error: %s", strerror(errno));
		exit(1);
	}

	printf("%s\n", buffer);
	return 0;
}
