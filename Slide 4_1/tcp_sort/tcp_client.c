#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
#include<arpa/inet.h>

void main(argc,argv)
int argc;
char *argv[];
{
  char hostname[50];
  int portno;
  int sock_1;
  static struct sockaddr_in sock_name; 
  struct hostent *hostentptr;
  int retval;
  int data[10], count, i;

  if(argc < 3) {
   printf("Usage: client <hostname> <port#>\n");
   exit(-1);
  }

  strcpy(hostname,argv[1]);
  portno = atoi(argv[2]);

  if ((sock_1 = socket(AF_INET,SOCK_STREAM,0)) == -1) {
     printf("socket error\n");
     exit(-1);
  }
  if ((hostentptr = gethostbyname(hostname)) == NULL) {
     printf("gethostbyname error\n");
     close(sock_1);
     exit(-1);
  }

  sock_name.sin_family = AF_INET;
  sock_name.sin_port = htons(portno);
  sock_name.sin_addr = *((struct in_addr *)hostentptr->h_addr);

  if (retval = connect(sock_1,(const struct sockaddr *)&sock_name,sizeof(sock_name))) {
     printf("connect error\n");
     close(sock_1);
     exit(-1);
  }

  printf("Enter number of values (up to 10): ");
  scanf("%d", &count);

  if (count > 10) {
     printf("Error: too many values\n");
     close(sock_1);
     exit(-1);
  }
  printf("Enter %d integers:\n", count);
  for(i=0; i<count; i++) {
     scanf("%d", &data[i]);
  }

  // Send count and data
  write(sock_1, &count, sizeof(int));
  write(sock_1, data, count * sizeof(int));

  // Receive sorted data
  read(sock_1, data, count * sizeof(int));

  printf("Sorted results: ");
  for(i=0; i<count; i++) {
     printf("%d ", data[i]);
  }
  printf("\n");

  close(sock_1);
}
