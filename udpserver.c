#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <strings.h>
#include <stdio.h>

#define PORT 28001
#define BUFSIZE 1024


// Author: William Nester Tamayo
void error(char *msg)
{
	perror(msg);
	exit(1);
}

int main(int argc, char **argv){
	int sockfd; /* socket */
	int length;
	int i;
	int size;
	socklen_t addrlen;
 	struct sockaddr_in server; /* server's addr */
 	struct sockaddr_in client; /* client addr */
 	char buffer[BUFSIZE]; /* message buf */
	
	sockfd=socket(AF_INET, SOCK_DGRAM, 0);
	if (sockfd < 0) 
    		error("ERROR opening socket");
	length = sizeof(server);
	bzero(&server,length);
	server.sin_addr.s_addr = htonl(INADDR_ANY);
	server.sin_port = htons(PORT);
	i = bind(sockfd, (struct sockaddr *) &server, sizeof(server));
	if( i < 0) {
		error("ERROR binding");
	} else {
		printf("Simple UDP server working!\n");
		addrlen = sizeof(struct sockaddr_in);
		}
	while(1){
		size = recvfrom(sockfd, buffer, BUFSIZE, 0, (struct sockaddr*)&client,&addrlen);
		if (size < 0){
			 error("ERROR recvfrom");
			}
		printf("Here is the message: %s\n",buffer);	
	}
}
