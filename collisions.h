#include "SDL2/SDL.h"
#include <stdbool.h>
#include "Player.h"
struct guy
{
    float x,y; 
    short life; 
    char name[];     
};typedef struct guy Guy; 

struct spike
{
    int x,y; 
};typedef struct spike Spike; 
struct ledge
{
    float x,y,w,h;//x y för vart o w h för storlek
}; typedef struct ledge Ledge; 
struct shield
{
    int x,y; 
};typedef struct shield Shield; 
struct grass
{
    float w,h; 
};typedef struct grass Grass; 
struct heart
{
    int x,y; 
};typedef struct heart Heart;
struct bubble
{
    int x,y; 
}; typedef struct bubble Bubble; 
struct finishline
{
    int x,y; 
};typedef struct finishline Finishline; 
struct gameState
{
    SDL_Renderer *renderer; 
    //SDL_Texture *guyFrames[2];
    SDL_Texture *ledgeFrame; 
    SDL_Texture *grass; 
    SDL_Texture *spike; 
    SDL_Texture *shieldFrame; 
    SDL_Texture *HearTexture; 
    SDL_Texture *bubbleFrame; 
    SDL_Texture *finishFrame; 
    SDL_Texture *gameoverFrame;

    Heart hearts[3]; 
    Spike spikeReg[10];
    Ledge ledgeReg[100]; 
    Shield shieldReg[5];

    Bubble bubbleBackground; 
    Grass grassBackground; 
    Finishline line; 
    float gameTimer; 
    
    Player player; //previously was Guy gubbe
};typedef struct gameState GameState; 

bool collisionBetweenPlayers(SDL_Rect *rect1, SDL_Rect *rect2);
bool collisionBetweenGuys(Player p1, Player p2);

void colisionWithWalls(Player player, SDL_Rect *dest,int winWidth, int winHeight);
void coillisionDetect(GameState *game, Player player);
int coillisionDetectonSpike(GameState *game, Player player, float timer);
int collisionsDetectOnShield(GameState *game, Player player); 
void powerUp(GameState *game, Player player, float *timer); 
int getHurt(GameState *game,Player player, int health,float timer); 
int finishLineDec(GameState *game,Player player);
