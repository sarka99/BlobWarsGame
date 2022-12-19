#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include "Player.h"
#define LEDGEMAX 100
#define SDL_MAIN_HANDLED
#define SDL_MAIN_HANDLED
#define WINDOW_WIDTH (600)
#define WINDOW_HEIGHT (400)
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_mixer.h"
#include "SDL2/SDL_net.h"
#include "game.h"
#include "map.h"

int main(int argc, char *argv[])
{
    srand(time(NULL));
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window *window = SDL_CreateWindow("BlobWars", SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,600,400,0);
    SDL_Renderer *renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC); 
    GameState game;
    game.renderer = renderer;
    Player player1, player2, player3, player4;
    int health = 3; 

    player1 = createPlayer(50, 75, 1, health);
    player2 = createPlayer(150,75,2,health);
    player3 = createPlayer(200, 75, 3, health);
    player4 = createPlayer(250, 75, 4, health);


    SDL_Event event;
    int done = 0;
    UDPsocket sd;
	IPaddress srvadd;
    srvadd.port = 2000;
	UDPpacket *p;
    UDPpacket *pRecieve;
    int recieveID;
    int x_oldPos;
    int y_oldPos;
    int x_newPos;
    int y_newPos;
    int otherPlayerX;
    int otherPlayerY;
    int startingPlayer = 1;
    int playerCount = 1;

    if (SDLNet_Init() < 0)
	{
		fprintf(stderr, "SDLNet_Init: %s\n", SDLNet_GetError());
		exit(EXIT_FAILURE);
	}

    if (!(sd = SDLNet_UDP_Open(0)))
	{
		fprintf(stderr, "SDLNet_UDP_Open: %s\n", SDLNet_GetError());
        printf("called from main");
		exit(EXIT_FAILURE);
	}

   // Resolve server name  
	if (SDLNet_ResolveHost(&srvadd, "127.0.0.1", 2000) == -1)
	{
		fprintf(stderr, "SDLNet_ResolveHost(192.0.0.1 2000): %s\n", SDLNet_GetError());
		exit(EXIT_FAILURE);
	}

    if (!((p = SDLNet_AllocPacket(512))&& (pRecieve = SDLNet_AllocPacket(512))))
	{
		fprintf(stderr, "SDLNet_AllocPacket: %s\n", SDLNet_GetError());
		exit(EXIT_FAILURE);
	}

    // attempt to initialize graphics and timer system
    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER) != 0)
    {
        printf("error initializing SDL: %s\n", SDL_GetError());
        return 1;
    }
    
    
    loadGame(&game,player1,player2, player3, player4);
    int size = 1;
    SDL_Texture *playerTexture = NULL;
    
    Player allPlayers[] = {player1, player2, player3, player4};

    SDL_Rect rect1, rect2, rect3, rect4;
    float timer = 5; 
    //int done = 0;


    
    while (!done)
    {
        timer = timer + 0.01666667;
        if(finishLineDec(&game, player1))
        {
            SDL_Delay(1000);
            break;
        }
      
        //  Checks for events
        done = processEvenets(window, player1, allPlayers, size);

        //wall boundary collision detection
        colisionWithWalls(player1,&rect1,WINDOW_WIDTH,WINDOW_HEIGHT);
                                                                     
        //Ledge
        coillisionDetect(&game,player1);

        //Spike
        health = getHurt(&game,player1,health,timer); 



        powerUp(&game,player1,&timer); 
        if (timer<=5)
        {
            game.bubbleBackground.x = getPlayerX(player1)-5;
            game.bubbleBackground.y = getPlayerY(player1)-5; 
        }else
        {
            game.bubbleBackground.x=-1000; 
            game.bubbleBackground.y=-1000; 
        }
        

        x_newPos = getPlayerX(player1);
        y_newPos = getPlayerY(player1);

   
    if ((playerCount == 1 && startingPlayer == 1)||(x_oldPos != getPlayerX(player1) || y_oldPos != getPlayerY(player1))){
        //the host will send this data
        sprintf((char *)p->data, "%d %d\n", x_newPos, y_newPos);
        p->address.host = (srvadd).host;
        p->address.port = (srvadd).port; 
        p->len = strlen((char *)p->data) + 1;
        SDLNet_UDP_Send(sd, -1, p);
        x_oldPos = getPlayerX(player1);
        y_oldPos = getPlayerY(player1);
        playerCount = 0;
    }        

        if(SDLNet_UDP_Recv(sd,pRecieve)){
            //receive the data as a client
            sscanf((char *)pRecieve->data, "%d %d %d", &otherPlayerX, &otherPlayerY, &recieveID);         
        }
        moveAllPlayers(allPlayers,recieveID,otherPlayerX,otherPlayerY);
        doRender(renderer, &game, player1,player2,player3,player4);    
        
    }
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyTexture(game.spike);
    SDL_Quit();

    return 0;
}
