//
//  node.c
//  CapstoneLab10
//
//  Created by Chris on 11/28/18.
//  Copyright © 2018 Chris. All rights reserved.
//

#include <fcntl.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include "pathCosts.h"

//#define NODES 3
#define number 3
#define INF 10000
#define LS_PORT 6060


struct NODELS{
    int D[NODES];
    int P[NODES];
    int n;
};

void *LSthread(void* arg);
void tcpClientLS(struct NODELS myTable);


struct NODELS current;

int main(){
    //link state part
    int i=0;
    current.n=0;
    for(i=0;i<number;i++) //initialize weight and predecessor and Nprime
    {
        current.P[i]=current.n;
        current.D[i]=C[current.n][i];
    }
    tcpClientLS(current);
    
    int sockfd=socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in servaddr; //creates server structure
    memset(&servaddr,0,sizeof(servaddr)); //makes memory of servAddr =0
    
    servaddr.sin_family=AF_INET;
    servaddr.sin_port=htons(LS_PORT);
    servaddr.sin_addr.s_addr=hton
    
    
    l(INADDR_ANY);

    int* threadArg;
    if(bind(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr)))
    {
        perror("bind\n");
        exit(1);
    }
    pthread_t threadId[100];
    while(1)
    {
        if(listen(sockfd,NODES)!=0)
        {
            perror("listen\n");
            exit(2);
        }
        int sockfdConn=accept(sockfd,NULL,NULL);
        threadArg=&sockfdConn;
        pthread_create(&threadId[i],NULL,LSthread,(void*)threadArg);
        i++;
    }

}

void *LSthread(void* arg){ //struct will be arg
    
    void* recv = NULL;
    struct NODELS* received; //casting arg to struct*pointer
    int sock=(int)arg;
    read(sock,recv,sizeof(struct NODELS));
    received=(struct NODELS*)recv;

    int loopmin=10000;
    int start=received->n;
    
    int N[6];
    int Nprime[6],count,nextnode = -1,i,j;
//    char node[6];
    
    for(i=0;i<number;i++) //initialize weight and predecessor and Nprime
    {
        Nprime[i]=0; //1=node is present 0=node is not present
        N[i]=1;
    }
    
    Nprime[start]=1;
    N[start]=0;
    count=1;
    current.D[start]=0;
    
    while(count<number-1)
    {
        loopmin=10000;
        
        for(i=0;i<number;i++)
            if(current.D[i]<loopmin&&Nprime[i]==0) //finds the minimum weight
            {
                loopmin=current.D[i];
                nextnode=i;
            }
        
        Nprime[nextnode]=1; //takes node from N and puts it in Nprime
        N[nextnode]=0;
        for(i=0;i<number;i++) //checks other paths
        {
            if(N[i]==1) //if node is N
            {
                if(loopmin+received->D[i]<current.D[i]) //if the min weight plus the distance from the next node to the current node
                {
                    current.D[i]=loopmin+received->D[i];
                    current.P[i]=nextnode;
                }
            }
        }
        count++;
    }
    
    
    for(i=0;i<number;i++)
    {
        if(i!=start) //print all except node u to node u
        {
            printf("\nCost to get from u to node ");
            if(i==1)
                printf("v = %d",current.D[i]); //prints according to their name value (u=0 v=1 w=2 x=3 y=4 z=5)
            if(i==2)
                printf("w = %d",current.D[i]);
            if(i==3)
                printf("x = %d",current.D[i]);
            if(i==4)
                printf("y = %d",current.D[i]);
            if(i==5)
                printf("z = %d",current.D[i]);
            printf("\nPath = %d ",i);
            j=i;
            j=current.P[j]; //prints node before it (works because not printing start node)
            printf("<---- %d",j);
            while(j!=start)
            {
                j=current.P[j];
                printf(" <---- %d",j);
            }
            
        }
    }
    printf("\n u=0 v=1 w=2 x=3 y=4 z=5 a=6\n");
    recv=(void*)received;
    write(sock, recv, sizeof(struct NODELS));
    close(sock);
    return 0;
}

void tcpClientLS(struct NODELS myTable){
    
    //Define socket structure to fill in Ip address and port
    struct sockaddr_in server;
    
    struct hostent *host_info;
    
    //value for file descriptor
    int sockfd;
    
    char server_name[15];
    
    //Create socket with AF_INET domain, and type SOCK_STREAM (for TCP transport protocol)
    //It returns a file descriptor in case of success, or -1 in case of failure
    sockfd = socket(AF_INET,SOCK_STREAM,0);
    if(sockfd<0) {
        perror("creating stream socket");
        exit(1);
    }
    
    printf("Updating neighbors...\n");
    int i;
    for(i=0; i< NODES; i++){
        if(strcmp(ipAddresses[i],"0") != 0){
            printf("Sending update to node : %d, ip: %s\n", i, ipAddresses[i]);
            strcpy(server_name, ipAddresses[i]);
            
            //gethostbyname() returns a hostent type struct, by searching for it with its hostname
            //If the host is unknown, the program exits with error
            host_info=gethostbyname(server_name);
            
            if(host_info==NULL){
                fprintf(stderr,":unknown host: %s\n",server_name);
                exit(2);
            }
            
            /*set up the server's socket address, then connect*/
            server.sin_family=host_info->h_addrtype;
            memcpy((char *)&server.sin_addr,host_info->h_addr,host_info->h_length);
            //Assign socket to port 5050
            server.sin_port=htons(LS_PORT);
            
            if(connect(sockfd,(struct sockaddr *)&server,sizeof (server))<0){
                perror("connecting to server");
                exit(3);
            }
            
            printf("\nClient: connect to server %s\n",server_name);
            
            //Tries to write into socket the value of outline
            if(write(sockfd, &myTable,sizeof(struct NODELS))<0)
                printf("writing to server failed\n");
            
            memset(&server_name[0], 0, sizeof(server_name));
        }
        
    }
    printf("Done updating.\n");
    
}
