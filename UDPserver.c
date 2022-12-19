#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_mixer.h"
#include "SDL2/SDL_net.h"

int main(int argc, char **argv)
{
    UDPsocket sd; //socket descriptor 
    IPaddress srvadd;       // pointer to packet memory 
    UDPpacket *pRecieve;
    UDPpacket *pSent;
    Uint32 IPclient1 = 0;  
    Uint32 IPclient2 = 0;
    Uint32 portClient1 = 0;
    Uint32 portClient2 = 0;
    int quit, nrOfConnections;
    int a, b;

    while(true)   //server is on until terminate
    {

	    if (SDLNet_Init() < 0)
	    {
		    fprintf(stderr, "SDLNet_Init: %s\n", SDLNet_GetError());        //initiliazes SDL_net
		    exit(EXIT_FAILURE);
	    }

        if(!(sd = SDLNet_UDP_Open(2000)))
        {
            fprintf(stderr, "SDLNet_UDP_Open: %s\n", SDLNet_GetError());  //Open socket
            exit(EXIT_FAILURE);
        }

        if (!((pSent = SDLNet_AllocPacket(512))&&(pRecieve = SDLNet_AllocPacket(512))))
	    {
		    fprintf(stderr, "SDLNet_AllocPacket: %s\n", SDLNet_GetError());  //Makes space for packet
		    exit(EXIT_FAILURE);
	    }

        quit = 0;
        
        while(!quit)              //main loop
        {
        /* Wait a packet. UDP_Recv returns != 0 if a packet is coming */
		if (SDLNet_UDP_Recv(sd, pRecieve))
		{
			printf("UDP Packet incoming\n");
			printf("\tData:    %s\n", (char *)pRecive->data);
			printf("\tAddress: %x %x\n", pRecive->address.host, pRecive->address.port);
            
            if(IPclient1 == 0 && portClient1 == 0){
                printf("Client 1\n");
                IPclient1 = pRecieve->address.host;
                portClient1 = pRecieve->address.port;
            }else if(pRecieve->address.port != portClient1  && IPclient2 == 0){
                printf("Client 2\n");
                IPclient2 = pRecieve->address.host;
                portClient2 = pRecieve->address.port;
            }else{
                if (pRecieve->address.port == portClient1){
                    printf("Recived data\n");
                    if(IPclient2 != 0){
                        printf("Send to Client 2\n");
                        pSent->address.host = IPclient2;	/* Set the destination host */
		                pSent->address.port = portClient2;
                        sscanf((char * )pRecieve->data, "%d %d\n", &a, &b);
                        printf("%d %d\n", a, b, 1);
                        sprintf((char *)pSent->data, "%d %d %d\n", a,  b, 1);
                        pSent->len = strlen((char *)pSent->data) + 1;
                        SDLNet_UDP_Send(sd, -1, pSent);
                    }
                } else if (pRecieve->address.port == portClient2){
                    printf("Send to Client 1\n");    
                    pSent->address.host = IPclient1;	/* Set the destination host */
		            pSent->address.port = portClient1;
                    sscanf((char * )pRecieve->data, "%d %d\n", &a, &b);
                    printf("%d %d\n", a, b);
                    sprintf((char *)pSent->data, "%d %d %d\n", a, b,2);
                    pSent->len = strlen((char *)pSent->data) + 1;
                    SDLNet_UDP_Send(sd, -1, pSent);
                }
                
            }
            

			/* Quit if packet contains "quit" */
			if (strcmp((char *)pSent->data, "quit") == 0)
				quit = 1;
		}		
        }


    }
    /* Clean and exit */
	SDLNet_FreePacket(pSent);
    SDLNet_FreePacket(pRecieve);
	SDLNet_Quit();
	return EXIT_SUCCESS;


}