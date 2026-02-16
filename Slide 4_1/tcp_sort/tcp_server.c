#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <errno.h>
#include <sys/types.h>
#include <ctype.h>

int compare(const void *a, const void *b) {
   return (*(int*)a - *(int*)b);
}

void main()
{
   int portno = 5789;
   int sock_1, sock_2;
   static struct sockaddr_in sock_name, client_info;
   int retval, len;
   int count, data[10];

   if ((sock_1 = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
      printf("socket error\n");
      exit(-1);
   }

   int opt = 1;
   setsockopt(sock_1, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

   sock_name.sin_family = AF_INET;
   sock_name.sin_port = htons(portno);
   sock_name.sin_addr.s_addr = htonl(INADDR_ANY);

   if (retval = bind(sock_1, (const struct sockaddr *)&sock_name, sizeof(sock_name))) {
      printf("bind error\n");
      close(sock_1);
      exit(-1);
   }

   if (retval = listen(sock_1, 5)) {
      printf("listen error\n");
      close(sock_1);
      exit(-1);
   }

   len = sizeof(client_info);
   sock_2 = accept(sock_1, (struct sockaddr *)&client_info, &len);
   if (sock_2 < 0) {
      printf("accept error\n");
      close(sock_1);
      exit(-1);
   }

   // Receive number of elements
   read(sock_2, &count, sizeof(int));
   
   // Receive the array
   read(sock_2, data, count * sizeof(int));

   // Sort data using qsort
   qsort(data, count, sizeof(int), compare);

   // Send back sorted data
   write(sock_2, data, count * sizeof(int));

   close(sock_1);
   close(sock_2);
}
