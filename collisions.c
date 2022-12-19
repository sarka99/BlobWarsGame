#include <stdbool.h>
#include "collisions.h"
#include "SDL2/SDL.h"
#include "Player.h"

void colisionWithWalls(Player player, SDL_Rect *dest,
                       int winWidth, int winHeight)
{
    // left corner of map
    if (getPlayerX(player) <= 0)
    {
        setPlayerX(player, 0);
    }
    // upper corner of map
    if (getPlayerY(player) <= 0)
    {
        setPlayerY(player, 0);
    }
    // right corner of map
    if (getPlayerX(player) >= winWidth - dest->w)
    {
        float newPosUpper = winWidth - dest->w;
        setPlayerX(player, newPosUpper);
    }
    // bottom corner of map
    if (getPlayerY(player) >= winHeight - dest->h)
    {
        float newPosCorner = winHeight - dest->h;
        setPlayerY(player,newPosCorner);
    }
}
bool collisionBetweenPlayers(SDL_Rect *rect1, SDL_Rect *rect2)
{
    if (rect1->y >= rect2->y + rect2->h)
    {
        return 0;
    }
    if (rect1->x >= rect2->x + rect2->w)
    {
        return 0;
    }
    if (rect1->y + rect1->h <= rect2->y)
    {
        return 0;
    }
    if (rect1->x + rect1->w <= rect2->x)
    {
        return 0;
    }
    return 1;
}

bool collisionBetweenGuys(Player p1, Player p2)
{
    SDL_Rect rect1 = {getPlayerX(p1), getPlayerY(p1), 50, 50};
    SDL_Rect rect2 = {getPlayerX(p2), getPlayerY(p2), 50, 50};
    return collisionBetweenPlayers(&rect1, &rect2);
}

void coillisionDetect(GameState *game, Player player) //tile collision
{
    for (int i = 0; i < 100; i++)
    {
        float manWidth = 20, mHeight=20;
        float manX = getPlayerX(player), manY= getPlayerY(player);
        float ledgeX = game->ledgeReg[i].x, ledgeY = game->ledgeReg[i].y, ledgeWidth = game->ledgeReg[i].w, ledgeHeight= game->ledgeReg[i].h; 

        if (manY+mHeight> ledgeY && manY <ledgeY + ledgeHeight)
        {
            
            if(manX<ledgeX+ledgeWidth && manX+manWidth > ledgeX+ledgeWidth)
            {
                setPlayerX(player, ledgeX + ledgeWidth);
                manX= ledgeX+ledgeWidth; 
            }
            else if(manX+manWidth > ledgeX && manX<ledgeX)
            {
                setPlayerX(player, ledgeX-manWidth);
                manX= ledgeX-manWidth;  
            }
        }
        if (manX+manWidth>ledgeX && manX<ledgeX+ledgeWidth)
        {
            if (manY<ledgeY+ledgeHeight && manY>ledgeY)
            {
                setPlayerY(player, ledgeY + ledgeHeight);
                   
            }
            else if(manY + mHeight>ledgeY && manY<ledgeY)
            {
                setPlayerY(player, ledgeY - mHeight);
                manY = ledgeY+ledgeHeight;
            }
        }  
    } 
}
int coillisionDetectonSpike(GameState *game,Player player,float timer) //tile collision
{
    for (int i = 0; i < 10; i++)
    {
        float manWidth = 20, mHeight=20;
        float manX = getPlayerX(player), manY= getPlayerY(player);
        float ledgeX = game->spikeReg[i].x, ledgeY = game->spikeReg[i].y, ledgeWidth = 31, ledgeHeight= 31; 
        if (timer < 5)
        {
            
            return 0;
        }
        
        if (manY+mHeight> ledgeY && manY <ledgeY + ledgeHeight)
        {
            
            if(manX<ledgeX+ledgeWidth && manX+manWidth > ledgeX+ledgeWidth)
            {  
                setPlayerX(player, ledgeX + ledgeWidth+30);
                manX= ledgeX+ledgeWidth+30;   
                return 1; 
            }
            else if(manX+manWidth > ledgeX && manX<ledgeX)
            {
                setPlayerX(player, ledgeX-manWidth-30);
                manX= ledgeX-manWidth-30; 
                return 1; 
            }
        }
        if (manX+manWidth>ledgeX && manX<ledgeX+ledgeWidth)
        {
            if (manY<ledgeY+ledgeHeight && manY>ledgeY)
            {
                setPlayerY(player, ledgeY + ledgeHeight+30);
                return 1; 
            }
            else if(manY + mHeight>ledgeY && manY<ledgeY)
            {
                setPlayerY(player, ledgeY - mHeight-30);
                manY = ledgeY+ledgeHeight+30;
                return 1; 
            }
        }  
    } 
    return 0; 
}
int collisionsDetectOnShield(GameState *game, Player player)
{
    for (int i = 0; i < 5; i++)
    {
        float manWidth = 20, mHeight=20;
        float manX = getPlayerX(player), manY= getPlayerY(player);
        float ledgeX = game->shieldReg[i].x, ledgeY = game->shieldReg[i].y, ledgeWidth = 27, ledgeHeight= 27;     
        if (manY+mHeight> ledgeY && manY <ledgeY + ledgeHeight)
        {
            
            if(manX<ledgeX+ledgeWidth && manX+manWidth > ledgeX+ledgeWidth)
            {
                game->shieldReg[i].x = -99; 
                game->shieldReg[i].y = -99; 
                return 1; 
              
            }
            else if(manX+manWidth > ledgeX && manX<ledgeX)
            {
                 game->shieldReg[i].x = -99; 
                game->shieldReg[i].y = -99;
                return 1; 
            }
        }
        if (manX+manWidth>ledgeX && manX<ledgeX+ledgeWidth)
        {
            if (manY<ledgeY+ledgeHeight && manY>ledgeY)
            {
                game->shieldReg[i].x = -99; 
                game->shieldReg[i].y = -99;
                return 1; 
            }
            else if(manY + mHeight>ledgeY && manY<ledgeY)
            {
                game->shieldReg[i].x = -99; 
                game->shieldReg[i].y = -99;
                return 1; 
            }
        }  
    } 

    return 0; 
}
void powerUp(GameState *game, Player player, float *timer)
{
    
    while (collisionsDetectOnShield(game,player))
    {
        *timer = 0;               
        if (*timer==5)
        {
            break; 
        }  
    }  
}

int getHurt(GameState *game,Player player,int health,float timer)
{
    if(coillisionDetectonSpike(game,player,timer))
    {
    
        health = health -  1; 
        setHealth(player,health); 
        SDL_Delay(100);
        game->hearts[health].x = -100; //outside the map; 
        game->hearts[health].y = -100;    
        

    }   
    if (health==0)
    {
        setPlayerX(player,1);
        setPlayerY(player,1);
        for (int i = 0; i < 3; i++)
        {
            game->hearts[i].x = 470 + (i*50); 
            game->hearts[i].y = i;
        }
        health = 3; 
        setHealth(player,health);
    }
    return health; 
}
int finishLineDec(GameState *game,Player player)
{
    float manWidth = 20, mHeight=20;
    float manX = getPlayerX(player), manY= getPlayerY(player);
    float ledgeX = game->line.x, ledgeY = game->line.y, ledgeWidth = 20, ledgeHeight= 74;     
    if (manY+mHeight> ledgeY && manY <ledgeY + ledgeHeight)
    {
            
        if(manX<ledgeX+ledgeWidth && manX+manWidth > ledgeX+ledgeWidth)
        {   
            return 1; 
        }
        else if(manX+manWidth > ledgeX && manX<ledgeX)
        {
            return 1; 
        }
    }
    if (manX+manWidth>ledgeX && manX<ledgeX+ledgeWidth)
    {
        if (manY<ledgeY+ledgeHeight && manY>ledgeY)
        {
            return 1; 
        }
        else if(manY + mHeight>ledgeY && manY<ledgeY)
        {
            return 1; 
        }
    }  
    return 0; 
}
