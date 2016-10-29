/* Le programme pour le Client.c 
*
*  Fait par : EN NAKDI Tarik  ESIEA-SE1
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>

#include <errno.h>

/*


*/
#ifdef __WIN32__
   WORD versionWanted = MAKEWORD(1, 1);
   WSADATA wsaData;
   WSAStartup(versionWanted, &wsaData);
#endif

#ifdef __WIN32__
# include <winsock2.h>
#else
# include <sys/socket.h>
#endif

int main() //

{

        int socket, bytes_recu; //   
        char envoyer_data[1024],recu_data[1024];  // envoyer
        struct hostent *host;
        struct sockaddr_in server_addr;  

        host = gethostbyname("127.0.0.1");

        if ((socket = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
            perror("Socket");
            exit(1);
        }

        server_addr.sin_family = AF_INET;     
        server_addr.sin_port = htons(5000);   
        server_addr.sin_addr = *((struct in_addr *)host->h_addr);
        bzero(&(server_addr.sin_zero),8); 

        if (connect(sock, (struct sockaddr *)&server_addr,
                    sizeof(struct sockaddr)) == -1) 
        {
            perror("Connect");
            exit(1);
        }

        while(1)
        {
        
          bytes_recu=recu(sock,recu_data,1024,0);
          recu_data[bytes_recu] = '\0';
 
          if (strcmp(recu_data , "q") == 0 || strcmp(recu_data , "Q") == 0)
          {
           close(socket);
           break;
          }

          else
           printf("\n Information Recu = %s " , recu_data);
           
           printf("\n envoyer (q or Q to quit) : ");
           gets(envoyer_data);
           
          if (strcmp(envoyer_data , "q") != 0 && strcmp(envoyer_data , "Q") != 0)
           envoyer(socket,envoyer_data,strlen(envoyer_data), 0); 

          else
          {
           send(socket,envoyer_data,strlen(envoyer_data), 0);   
           close(socket);
           break;
          }
        
        }   
return 0;
}
