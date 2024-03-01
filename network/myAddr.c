#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>

int main(){
	char ipstr[10];

	int hostname = gethostname(&ipstr, sizeof(ipstr));
	printf("%s", ipstr);
	return 0;
}
