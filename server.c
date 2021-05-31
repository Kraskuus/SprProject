// server program for udp connection
#include <stdio.h>
#include <strings.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>




#define PORT 5000
#define MAXLINE 1000


   typedef struct Pacient{
    int years;
    int egn;
    char name[20];
    char diagnosa[20];
    char prognosa[30];
} Pacient;


void WriteToFile(Pacient pacient){

    int fd=open("regfile.bin",O_WRONLY | O_CREAT | O_APPEND, 0777 );

    write(fd,&pacient,sizeof(pacient));

    close(fd);
}

// Driver code
int main()
{   
    
  Pacient pacient[40];
    int sockfd;
    int command;
    int egn;
    int zapisifile = 0;
    int pacientind = 0;
    char buffer[MAXLINE];
    char *hello = "Hello from server";
    struct sockaddr_in servaddr, cliaddr;
      
    // Creating socket file descriptor
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }
      
    memset(&servaddr, 0, sizeof(servaddr));
    memset(&cliaddr, 0, sizeof(cliaddr));
      
    // Filling server information
    servaddr.sin_family    = AF_INET; // IPv4
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(PORT);
      
    // Bind the socket with the server address
    if ( bind(sockfd, (const struct sockaddr *)&servaddr, 
            sizeof(servaddr)) < 0 )
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
      
    int len, n, i;
  
    len = sizeof(cliaddr);  //len is value/resuslt
  for(;;){
n = recvfrom(sockfd, &command, sizeof(int), 
                MSG_WAITALL, ( struct sockaddr *) &cliaddr,
                &len);
printf("%d\n", command);
if(command==1){
    n = recvfrom(sockfd, &pacient[pacientind], sizeof(pacient[pacientind]), 
                MSG_WAITALL, ( struct sockaddr *) &cliaddr,
                &len);
  printf("%s\n", pacient[pacientind].name);
    pacientind++;
}else if(command==2){
    n = recvfrom(sockfd, &egn, sizeof(int), 
                MSG_WAITALL, ( struct sockaddr *) &cliaddr,
                &len);
    for(i=0;i<pacientind;i++){
        if(pacient[i].egn==egn){
    break;
        }

    }
    WriteToFile(pacient[i]);



 for(i=i+1;i<pacientind;i++){
    pacient[i-1]=pacient[i];

}
pacientind--;

}
else if(command==3){ sendto(sockfd, &pacientind, sizeof(int),
        MSG_CONFIRM, (const struct sockaddr *) &cliaddr, 
            sizeof(cliaddr));


    for(i=0;i<pacientind;i++){
       sendto(sockfd, &pacient[i], sizeof(pacient[i]),
        MSG_CONFIRM, (const struct sockaddr *) &cliaddr, 
            sizeof(cliaddr));
    }
}
else{
    Pacient umrqlpacient[40];
int fd=open("regfile.bin",O_RDONLY , 0777 );

while(read(fd,&umrqlpacient[zapisifile],sizeof(umrqlpacient[zapisifile]))!=0){
zapisifile++;

}

  close(fd);
sendto(sockfd, &zapisifile, sizeof(int),
        MSG_CONFIRM, (const struct sockaddr *) &cliaddr, 
            sizeof(cliaddr));



    for(i=0;i<zapisifile;i++){ 

       sendto(sockfd, &umrqlpacient[i], sizeof(umrqlpacient[i]),
        MSG_CONFIRM, (const struct sockaddr *) &cliaddr, 
            sizeof(cliaddr));

    }
    
}





   
    
  }
    
    printf("Client : %s\n", buffer);
    sendto(sockfd, (const char *)hello, strlen(hello), 
        MSG_CONFIRM, (const struct sockaddr *) &cliaddr,
            len);
    printf("Hello message sent.\n"); 
      
    return 0;
}
    
