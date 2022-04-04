//pass port no. as first argument.

#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
#include<netdb.h>
#include<netinet/in.h>


int main(int argc, char **argv)
{
	int	sockfd,n;
	struct sockaddr_in	servaddr;
	char	sendline[1024], recvline[1024];
	

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(atoi(argv[1]));
	inet_pton(AF_INET,"127.0.0.1", &servaddr.sin_addr);

	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
        for(;;)  {
          printf("Enter ur msg.\n");
	  scanf("%s",&sendline) ;
	  sendto(sockfd, sendline, strlen(sendline), 0, (struct sockaddr *)&servaddr, sizeof(servaddr));
	  n = recvfrom(sockfd, recvline,1024,0, NULL, NULL);
	  recvline[n] ='\0';	
	  puts(recvline);
        }
return 0;
}
 






	

