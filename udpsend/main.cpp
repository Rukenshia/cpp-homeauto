#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char**argv)
{
   int sockfd,n;
   unsigned int packets = 0;
   struct sockaddr_in servaddr,cliaddr;
   char sendline[1000] = "actor set bed_light 0";
   char recvline[1000];

   sockfd=socket(AF_INET,SOCK_DGRAM,0);

   memset(&servaddr,0,sizeof(servaddr));
   servaddr.sin_family = AF_INET;
   servaddr.sin_addr.s_addr=inet_addr("127.0.0.1");
   servaddr.sin_port=htons(4200);

   //while (fgets(sendline, 10000,stdin) != NULL)
   while (1)
   {
      sendto(sockfd,sendline,strlen(sendline),0,
             (struct sockaddr *)&servaddr,sizeof(servaddr));
      n=recvfrom(sockfd,recvline,10000,0,NULL,NULL);
      recvline[n]=0;
      printf("%s\tPACKET_NUM %d\n", recvline, ++packets);
   }
}
