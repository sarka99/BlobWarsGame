#include <stdio.h>
#include <stdlib.h>
#include "SDL2/SDL.h"
#include "collisions.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_mixer.h"
#include "SDL2/SDL_net.h"


int processEvenets(SDL_Window *window, Player player, Player allPlayers[], int length);
void beforeRender(SDL_Renderer *renderer);
SDL_Rect addToRenderer(SDL_Renderer *renderer, Player player, Player player2, Player player3, Player player4);
void loadGame(GameState *game, Player player1, Player player2, Player player3, Player player4);

SDL_Rect doRender(SDL_Renderer *renderer, GameState *game, Player player,Player player2, Player player3, Player player4);
void logicUpdate(GameState *game, UDPsocket *sd, IPaddress *srvadd, UDPpacket *p, Player player1);


