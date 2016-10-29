/* Le programme du servereur en commun */

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

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


int main()
{
        int socket, connected, bytes_recieved , true = 1;  
        char envoyer_data [1024] , recu_data[1024];       

        struct sockaddr_in server_addr,client_addr;    
        int sin_size;
        
        if ((socket = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
            perror("Socket");
            exit(1);
        }

        if (setsockopt(sock,SOL_SOCKET,SO_REUSEADDR,&true,sizeof(int)) == -1) {
            perror("Set-socket operation");
            exit(1);
        }
        
        server_addr.sin_family = AF_INET;         
        server_addr.sin_port = htons(5000);     
        server_addr.sin_addr.s_addr = INADDR_ANY; 
        bzero(&(server_addr.sin_zero),8); 

        if (bind(sock, (struct sockaddr *)&server_addr, sizeof(struct sockaddr))
                                                                       == -1) {
            perror("Unable to bind");
            exit(1);
        }

        if (listen(sock, 5) == -1) {
            perror("Listen");
            exit(1);
        }
		
	printf("\nTCPServer Waiting for client on port 5000");
        fflush(stdout);


        while(1)
        {  

            sin_size = sizeof(struct sockaddr_in);

            connected = accept(socket, (struct sockaddr *)&client_addr,&sin_size);

            printf("\n I got a connection from (%s , %d)",
                   inet_ntoa(client_addr.sin_addr),ntohs(client_addr.sin_port));

            while (1)
            {
              printf("\n envoyer (q or Q to quit) : ");
              gets(envoyer_data);
              
              if (strcmp(envoyer_data , "q") == 0 || strcmp(envoyer_data , "Q") == 0)
              {
                envoyer(connected, envoyer_data,strlen(envoyer_data), 0); 
                close(connected);
                break;
              }
               
              else
                 envoyer(connected, envoyer_data,strlen(envoyer_data), 0);  

              bytes_recu = recu(connected,recu_data,1024,0);

              recu_data[bytes_recu] = '\0';

              if (strcmp(recu_data , "q") == 0 || strcmp(recu_data , "Q") == 0)
              {
                close(connected);
                break;
              }

              else 
              printf("\n RECU DATA = %s " , recu_data);
              fflush(stdout);
            }
        }       

      close(sock);
      return 0;
} 
