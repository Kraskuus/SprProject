// udp client driver program
#include <stdio.h>
#include <strings.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>


  
#define PORT 5000
#define MAXLINE 1000
  
  typedef struct Pacient{
    int years;
    int egn;
    char name[20];
    char diagnosa[25];
    char prognosa[30];
} Pacient;
// Driver code

Pacient* Input(){
    
   Pacient *pacient=(Pacient*)malloc(sizeof(Pacient));
   printf("Vuvedi ime:");
      getc(stdin);

   fgets(pacient->name, 20,stdin);
   pacient->name[strcspn(pacient->name, "\n")] = 0;
   printf("Vuvedi Diagnosa: ");
    fgets(pacient->diagnosa, 25 ,stdin);
    pacient->diagnosa[strcspn(pacient->diagnosa, "\n")] = 0;
    printf("Vuvedi Prognasa: ");
    fgets(pacient->prognosa, 30 ,stdin);
    pacient->prognosa[strcspn(pacient->prognosa, "\n")] = 0;
    printf("Vuvedi godini:");
    scanf("%d",&pacient->years);
    printf("Vuvedi egn:");
    scanf("%d",&pacient->egn);

    return pacient;

   }


void Sendpacient(int sockfd, Pacient pacient){

     int n=write(sockfd, &pacient, sizeof(pacient));
     printf("N= %d\n",n );

}

int main() {

    Pacient pacient;
    int sockfd;
int i;
    int command;
    int egn;
    int pacientind;
    char buffer[MAXLINE];
    char *hello = "Hello from client";
    struct sockaddr_in     servaddr;
  
    // Creating socket file descriptor
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }
  
    memset(&servaddr, 0, sizeof(servaddr));
      
    // Filling server information
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = INADDR_ANY;
      
    int n, len;
      for(;;){ 
        printf("Izberi 1 za vuvejdane na pacient\n");
           printf("  Izberi 2 za iztrivane na pacient chrez eng i gi prashta vuv vechniq spisuk \n");
            printf(" Izberi 3 za show all pacients\n");
            printf(" Izberi 4, za da gi pokajesh ot vechniq spisuk !!! \n");
      scanf("%d",&command) ;

       sendto(sockfd, &command, sizeof(int),
        MSG_CONFIRM, (const struct sockaddr *) &servaddr, 
            sizeof(servaddr));

      if(command==1){
         printf("Izbor za vuvejdane na pacient: \n");
        Pacient* pacient= Input();
          sendto(sockfd, pacient, sizeof(*pacient),
        MSG_CONFIRM, (const struct sockaddr *) &servaddr, 
            sizeof(servaddr));
      }else if(command==2){
         printf("CHoose pacient EGN to be deleted: \n");

        scanf("%d",&egn);
        sendto(sockfd, &egn, sizeof(int),
        MSG_CONFIRM, (const struct sockaddr *) &servaddr, 
            sizeof(servaddr));

      }else if(command==3){
        printf("Pokazva vsichki pacienti: \n");

       n = recvfrom(sockfd, &pacientind, sizeof(int), 
                MSG_WAITALL, ( struct sockaddr *) &servaddr,
                &len);
printf("%d\n", pacientind);

for(i=0;i<pacientind;i++){
       n = recvfrom(sockfd, &pacient, sizeof(pacient), 
                MSG_WAITALL, ( struct sockaddr *) &servaddr,
                &len);
  printf("%s %d %d %s %s\n", pacient.name,pacient.egn,pacient.years,pacient.diagnosa,pacient.prognosa);
  
    }
      }else{
         n = recvfrom(sockfd, &pacientind, sizeof(int), 
                MSG_WAITALL, ( struct sockaddr *) &servaddr,
                &len);
printf("%d\n", pacientind);

for(i=0;i<pacientind;i++){
       n = recvfrom(sockfd, &pacient, sizeof(pacient), 
                MSG_WAITALL, ( struct sockaddr *) &servaddr,
                &len);
  printf("%s %d %d %s %s\n", pacient.name,pacient.egn,pacient.years,pacient.diagnosa,pacient.prognosa);
  
      }


       }
    }
    
    printf("Hello message sent.\n");
          
    n = recvfrom(sockfd, (char *)buffer, MAXLINE, 
                MSG_WAITALL, (struct sockaddr *) &servaddr,
                &len);
    buffer[n] = '\0';
    printf("Server : %s\n", buffer);
  
    close(sockfd);
    return 0;
}





