#ifndef Player_h
#define Player_h

#include <stdio.h>

typedef struct Player_type *Player;
Player createPlayer();
void setPlayerX(Player p, int x);
void setPlayerY(Player p, int y);
int getPlayerX(Player player);
int getPlayerY(Player player);
int getPlayerId(Player player);
void setHealth(Player player, int newHealth);
int getHealth(Player player);
void moveAllPlayers(Player players[], int recieveID, int a, int b);

#endif
