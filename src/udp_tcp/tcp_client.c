// Supply PORT no as first argument.

#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
#include<netdb.h>
#include<string.h>
int main(int argc ,char **argv)
{
   int sock;
   char msg[1024],buf[200];
   int n;


 struct hostent *host;
 struct sockaddr_in saddr;
 host=gethostbyname("127.0.0.1");
 sock=socket(AF_INET,SOCK_STREAM,0);
 saddr.sin_family=AF_INET;
 saddr.sin_port=htons(atoi(argv[1]));
 saddr.sin_addr=*((struct in_addr *)host->h_addr);
   if(connect(sock,(struct sockaddr *)&saddr,sizeof(struct sockaddr))==-1)   {
        perror("Connect error");
        exit(1);
     }

 printf("Server connected....\n");

for(;;) {
   printf("Enter a message:\n");
   gets(msg);
   send(sock,msg,1024,0);
   n=recv(sock,buf,1024,0);
   buf[n]='\0';
   printf("Echoed data: %s\n",buf);
  }
 return 0;
}
