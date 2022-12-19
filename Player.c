#include "Player.h"
#include <stdlib.h>
#include <SDL2/SDL.h>

struct Player_type
{
    int PLAYER_POSITION_X;
    int PLAYER_POSITION_Y;
    // SDL_Texture *playerTexture;
    int health;
    int id;
};
Player createPlayer(int x, int y, int id, int health)               //creates player
{
    Player p = malloc(sizeof(struct Player_type));                  //allocates the player to the memory
    p->PLAYER_POSITION_Y = y;
    p->PLAYER_POSITION_X = x;
    p->id = id;
    p->health = health;
    return p;
}

void setPlayerX(Player p, int x)
{
    p->PLAYER_POSITION_X = x;
}

int getPlayerId(Player player)
{

    return player->id;
}

void setPlayerY(Player p, int y)
{
    p->PLAYER_POSITION_Y = y;
}
int getPlayerX(Player p)
{
    return p->PLAYER_POSITION_X;
}
int getPlayerY(Player p)
{
    return p->PLAYER_POSITION_Y;
}
void setHealth(Player p, int newHealth){

    p->health = newHealth;
}

int getHealth(Player p){

    return p->health;
}
void moveAllPlayers(Player players[], int recieveID, int a, int b){
    if(recieveID == 1){                                                         //based on playerID, we move the player
        setPlayerX(players[1], a);
        setPlayerY(players[1], b);
        printf("the receive id here is: %d\n", recieveID);
    }else if (recieveID == 2){
        setPlayerX(players[1], a);
        setPlayerY(players[1], b);
        printf("the receive id here is: %d\n", recieveID);
    }else if (recieveID ==3){
        setPlayerX(players[2], a);
        setPlayerY(players[2], b);
        printf("the receive id here is: %d\n", recieveID);
    }else{
        setPlayerX(players[3], a);
        setPlayerY(players[3], b);
        printf("the receive id here is: %d\n", recieveID);
    }
      
}