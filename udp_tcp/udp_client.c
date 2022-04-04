//Supply port no. as first argument.

#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
#include<netdb.h>
#include<netinet/in.h>


int main(int argc, char **argv)
{
	int	sockfd,n;
	socklen_t sin_len; 
	struct sockaddr_in	servaddr,addr;
	char	sendline[1024], recvline[1024];
	

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(atoi(argv[1]));
	inet_pton(AF_INET,"127.0.0.1", &servaddr.sin_addr);

	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
        for(;;)  {
          printf("Enter ur msg.\n");
	  gets(sendline) ;
          sin_len=sizeof(addr);
	  sendto(sockfd, sendline,1024, 0, (struct sockaddr *)&servaddr, sizeof(struct sockaddr));
	  n = recvfrom(sockfd, recvline,1024,0,(struct sockaddr *)&addr, &sin_len);
	  recvline[n] ='\0';	
	  puts(recvline);
          printf("Msg Echoed by server:");
          printf("\n(%s,%d)\n",(char *)inet_ntoa(addr.sin_addr),ntohs(addr.sin_port));
        
        }
  return 0;
}
 






	

