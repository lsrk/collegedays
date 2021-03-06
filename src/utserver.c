
//Specify port no as first argument

#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<arpa/inet.h>



int main(int argc, char **argv)
{
	int	sockfd, connfd, udpfd, nready, maxfd;
	char	msg_udp[1024],msg_tcp[1024];
	pid_t	childpid;
	fd_set	rset;
	ssize_t	 n;
	socklen_t len;
	
	struct sockaddr_in	cliaddr, servaddr;
	
		/*  TCP socket */
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family      = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port        = htons(atoi(argv[1]));
	bind(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr));
	listen(sockfd, 10);


		/* UDP socket */
	udpfd = socket(AF_INET, SOCK_DGRAM, 0);
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family      = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port        = htons(atoi(argv[1]));
	bind(udpfd, (struct sockaddr *) &servaddr, sizeof(servaddr));





	FD_ZERO(&rset);
	maxfd =(sockfd>udpfd ?sockfd :udpfd ) + 1;
    
       for ( ; ; ) {
		FD_SET(sockfd, &rset);
		FD_SET(udpfd, &rset);
		printf("Server blocked in select.\n");
		nready = select(maxfd, &rset, NULL, NULL, NULL);
		if(nready>0)
                    printf("Server returned from select.\n");	

		if (FD_ISSET(sockfd, &rset)) {
			
                         len = sizeof(cliaddr);
			 connfd = accept(sockfd, (struct sockaddr *) &cliaddr, &len);
	
			if ((childpid = fork())==0) {	         /* child process */
				close(sockfd);			/* close listening socket */
				printf("Processing done by server child %d,for TCP client with connfd %d\n\n",getpid(),connfd);
				
                                  for(;;) {
                                   
                                   n=recv(connfd,msg_tcp,1024,0);
                                   send(connfd,msg_tcp,1024,0);
				   fflush(stdout);
                                 }
                             
			      exit(0);
			}
			
                       close(connfd);			/* parent server closes connected socket */
		  }

		if (FD_ISSET(udpfd, &rset)) {
			len = sizeof(cliaddr);
			n = recvfrom(udpfd, msg_udp,1024, 0, (struct sockaddr *) &cliaddr, &len);
			printf("UDP datagram received from.\n");
			printf("(%s,%d)\n",(char *)inet_ntoa(cliaddr.sin_addr),ntohs(cliaddr.sin_port));
			sendto(udpfd, msg_udp, n, 0, (struct sockaddr *) &cliaddr, len);
		  }
	}
 }

