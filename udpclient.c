#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <strings.h>
#include <stdio.h>

#define PORT 28001
#define TARGET_PORT 28001
#define BUFSIZE 1024 
#define homeIP 127.0.0.1

// Author: William Nester Tamayo

void error(char *msg)
{
	perror(msg);
	exit(1);
}

int main( int argc, char **argv){
	int sockfd;
	int size;
	int i;
	struct sockaddr_in target_pc; /* server's addr */
 	struct sockaddr_in me; /* client addr */
	char buffer[BUFSIZE];
	
	sockfd=socket(AF_INET, SOCK_DGRAM, 0);
	if (sockfd < 0) 
    		error("ERROR opening socket");
	target_pc.sin_family = AF_INET;
	target_pc.sin_port = htons(TARGET_PORT);
	me.sin_family = PF_INET;
	me.sin_port = htons(0);
	me.sin_addr.s_addr = htonl(INADDR_ANY);
	i = bind(sockfd, (struct sockaddr *) &me, sizeof(me));
	if( i < 0) {
		printf("bind result: %d\n", i);
		return -1;
	}
	target_pc.sin_addr.s_addr = inet_addr("127.0.0.1");

	printf("Please enter the message:\n");
	bzero(buffer,BUFSIZE);
	fgets(buffer, BUFSIZE - 1, stdin);
	int nbytes = strlen(buffer);
	int flags = 0;
	size = sendto(sockfd, (char *) buffer, nbytes,flags,(struct sockaddr *)&target_pc, sizeof(target_pc));
	if (size < 0){
		error("ERROR sendto");
	}
	else
		printf("send was succesful\n");
}
