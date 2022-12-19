#include "game.h"
#include "SDL2/SDL.h"
#include "Player.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_mixer.h"
#include "SDL2/SDL_net.h"
#include "map.h"

#define distanceToMove 5

int processEvenets(SDL_Window *window, Player player, Player allPlayers[], int length)
{

    SDL_Event event;
    int done = 0;


    while (SDL_PollEvent(&event) && event.type == SDL_QUIT)
    {

        switch (event.type)
        {
        // if close button was pressed exit game,return 1
        case SDL_WINDOWEVENT_CLOSE:
        {
            if (window)
            {
                SDL_DestroyWindow(window);
                window = NULL;
                done = 1;
            }
        }
        break;
        // IF esc key was pressed exit the game, return 1
        case SDL_KEYDOWN:
        {
            switch (event.key.keysym.sym)
            {
            case SDLK_ESCAPE:
                done = 1;
                break;
            }
        }
        break;
        case SDL_QUIT:
            done = 1;
            break;
        }
    }
    // gives a snapchat of which key was pressed, holds many keys
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    int directionX, directionY;
    directionX = directionY = 0;

    // if left was pressed move the player to the left

    if (state[SDL_SCANCODE_LEFT])
    {
        directionX -= distanceToMove;
        
    }
    if (state[SDL_SCANCODE_RIGHT])
    {
        directionX += distanceToMove;
    }
    if (state[SDL_SCANCODE_DOWN])
    {
        directionY += distanceToMove;
    }
    
    if (state[SDL_SCANCODE_UP])
    {
        directionY -= distanceToMove;
    }
   

   

    Player tempPlayer = createPlayer(0, 0, -1); // intial value for tempPlayer which help oss to check if we can move or not
    setPlayerX(tempPlayer, getPlayerX(player) + directionX);
    setPlayerY(tempPlayer, getPlayerY(player) + directionY);

    bool canMove = true;

    for (int i = 0; i < length; i++)
    {
        Player targetPlayer = allPlayers[i];
        if (getPlayerId(targetPlayer) == getPlayerId(player))
        {
            continue;
        }
        if (collisionBetweenGuys(targetPlayer, tempPlayer))
        {
            canMove = false;
            break;
        }
    }

    if (canMove)
    {
        setPlayerX(player, getPlayerX(tempPlayer));
        setPlayerY(player, getPlayerY(tempPlayer));
    }


    return done;
}

void beforeRender(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0); // set the drawing color to blue

    SDL_RenderClear(renderer); // Clear the screan (to blue)
}

SDL_Rect addToRenderer(SDL_Renderer *renderer, Player player,Player player2, Player player3, Player player4)
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // set the drawing color to white

    SDL_Rect rect = {getPlayerX(player), getPlayerY(player), 50, 50};
    SDL_Rect rect2 = {getPlayerX(player2), getPlayerY(player2), 50, 50};
    SDL_Rect rect3 = {getPlayerX(player3), getPlayerY(player3), 50, 50};
    SDL_Rect rect4 = {getPlayerX(player4), getPlayerY(player4), 50, 50};
    SDL_RenderFillRect(renderer, &rect);
    SDL_RenderFillRect(renderer, &rect2);
    SDL_RenderFillRect(renderer, &rect3);
    SDL_RenderFillRect(renderer, &rect4);

    return rect;
}
void loadGame(GameState *game, Player player1, Player player2, Player player3, Player player4)
{
   // game->gubbe.x = 5; 
   // game->gubbe.y = 5;
    setPlayerX(player1,5);
    setPlayerY(player1,5);
    setPlayerX(player2,50);
    setPlayerY(player2,5);
    setPlayerX(player3,100);
    setPlayerY(player3,5);
    setPlayerX(player4, 150);
    setPlayerY(player4, 5);
    SDL_Surface *surface = NULL; 
    
    surface = IMG_Load("assets/bubble.png");
    game->bubbleFrame = SDL_CreateTextureFromSurface(game->renderer,surface); 
    SDL_FreeSurface(surface); 
   
    surface = IMG_Load("assets/spike.png");
    game->spike = SDL_CreateTextureFromSurface(game->renderer,surface);
    SDL_FreeSurface(surface); 

    surface = IMG_Load("assets/wall2.png");
    game->ledgeFrame = SDL_CreateTextureFromSurface(game->renderer,surface);
    SDL_FreeSurface(surface); 

    surface = IMG_Load("assets/grass.png"); 
    game->grass = SDL_CreateTextureFromSurface(game->renderer,surface); 
    SDL_FreeSurface(surface); 

    surface = IMG_Load("assets/shield.png");
    game->shieldFrame = SDL_CreateTextureFromSurface(game->renderer,surface); 
    SDL_FreeSurface(surface); 

    surface = IMG_Load("assets/heart.png");
    game->HearTexture = SDL_CreateTextureFromSurface(game->renderer,surface); 
    SDL_FreeSurface(surface); 

    surface = IMG_Load("assets/finishline2.png"); 
    game->finishFrame = SDL_CreateTextureFromSurface(game->renderer,surface);
    SDL_FreeSurface(surface);

    surface = IMG_Load("assets/gameover.png");
    game->gameoverFrame = SDL_CreateTextureFromSurface(game->renderer,surface);
    SDL_FreeSurface(surface);
   
    if (surface == NULL)
   {
       printf("can't find images"); 
       SDL_Quit; 
       return; 
   }
    
    loadMap(game); 
}

SDL_Rect doRender(SDL_Renderer *renderer, GameState *game, Player player,Player player2, Player player3, Player player4 )
{

    
    

    
    SDL_Rect grassRect = {0, 0,600,400};
    SDL_RenderCopy(renderer,game->grass,NULL,&grassRect); 



    SDL_Rect finishRect = {game->line.x,game->line.y,20,74};
    SDL_RenderCopy(renderer,game->finishFrame,NULL,&finishRect); 

    SDL_SetRenderDrawColor(renderer,255,255,255,255); // set the drawing color to white
    SDL_Rect rect = {getPlayerX(player),getPlayerY(player),20,20};
    SDL_RenderFillRect(renderer,&rect);

    SDL_SetRenderDrawColor(renderer,255,255,255,255); // set the drawing color to white
    SDL_Rect rect2 = {getPlayerX(player2),getPlayerY(player2),20,20};
    SDL_RenderFillRect(renderer,&rect2);

    SDL_SetRenderDrawColor(renderer,255,255,255,255); // set the drawing color to white
    SDL_Rect rect3 = {getPlayerX(player3),getPlayerY(player3),20,20};
    SDL_RenderFillRect(renderer,&rect3);

    SDL_SetRenderDrawColor(renderer,255,255,255,255); // set the drawing color to white
    SDL_Rect rect4 = {getPlayerX(player4),getPlayerY(player4),20,20};
    SDL_RenderFillRect(renderer,&rect4);

    //double buffering, makes graphics better

    for (int i = 0; i < 10; i++)
    {
        SDL_Rect spikeRect = {game->spikeReg[i].x,game->spikeReg[i].y,32,32};
        SDL_RenderCopy(renderer,game->spike,NULL,&spikeRect);
    }
    for (int i = 0; i < 5; i++)
    {
        SDL_Rect shieldRect = {game->shieldReg[i].x,game->shieldReg[i].y,32,32}; 
        SDL_RenderCopy(renderer,game->shieldFrame,NULL,&shieldRect);
    }
    for (int i = 0; i < 100; i++)
    {
        SDL_Rect ledgeRect = {game->ledgeReg[i].x,game->ledgeReg[i].y,game->ledgeReg[i].w,game->ledgeReg[i].h};
        SDL_RenderCopy(renderer,game->ledgeFrame,NULL,&ledgeRect);
    }
    for (int i = 0; i < 3; i++)
    {
        SDL_Rect heartRect = {game->hearts[i].x,game->hearts[i].y, 32,32}; 
        SDL_RenderCopy(renderer,game->HearTexture,NULL,&heartRect); 
    }

    SDL_Rect bubbleRect = {game->bubbleBackground.x,game->bubbleBackground.y,32,32};
    SDL_RenderCopy(renderer,game->bubbleFrame,NULL,&bubbleRect); 
    if (finishLineDec(game,player))
    {
        SDL_Rect gameoverRect = {0,0,600,400};
        SDL_RenderCopy(renderer,game->gameoverFrame,NULL,&gameoverRect);
    }
    

    
    
    SDL_RenderPresent(renderer); 
    return rect;
}


