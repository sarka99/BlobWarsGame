#include <stdio.h>
//#include "map.h"oll
#include "collisions.h"
#include "map.h"

void loadMap(GameState *game)
{                                           //asigning width, height and x - y coordinates
    game->line.x = 550; 
    game->line.y=330;
    
    game->spikeReg[0].x = 35;
    game->spikeReg[0].y =  316;

    game->spikeReg[1].x = 0;
    game->spikeReg[1].y =  170;

    game->spikeReg[2].x = 290;
    game->spikeReg[2].y =  240;   

    game->spikeReg[3].x = 215;
    game->spikeReg[3].y =  45; 

    game->spikeReg[4].x = 350;
    game->spikeReg[4].y =  10;

    game->spikeReg[5].x = 463;
    game->spikeReg[5].y =  45;

    game->spikeReg[6].x = 545;
    game->spikeReg[6].y =  160;
    
    game->spikeReg[7].x = 463;
    game->spikeReg[7].y =  45;

    game->spikeReg[8].x = 115;
    game->spikeReg[8].y =  25;

    game->spikeReg[9].x = 370;
    game->spikeReg[9].y =  280;

    for (int i = 0; i < 5; i++)
    {
        game->shieldReg[i].x = rand()%550; 
        game->shieldReg[i].y = rand()%350;
    }
    for (int i = 0; i < 3; i++)
    {
        game->hearts[i].x = 470 + (i*50); 
        game->hearts[i].y = i;
    }
    game->bubbleBackground.x = -1000;
    game->bubbleBackground.y = -1000; 


    //init ledeges
    game->ledgeReg[0].w = 50;
    game->ledgeReg[0].h = 15;
    game->ledgeReg[0].x = 0;
    game->ledgeReg[0].y = 200;

    game->ledgeReg[1].w = 60;
    game->ledgeReg[1].h = 15;
    game->ledgeReg[1].x = 75+20;
    game->ledgeReg[1].y = 100-40;

    game->ledgeReg[2].w = 15;
    game->ledgeReg[2].h = 72;
    game->ledgeReg[2].x = 75+20;
    game->ledgeReg[2].y = 100-40;
                                                                    
    game->ledgeReg[3].w = 200;
    game->ledgeReg[3].h = 15;
    game->ledgeReg[3].x = 75+20;
    game->ledgeReg[3].y = 172-40;

    game->ledgeReg[4].w = 15;
    game->ledgeReg[4].h = 146;
    game->ledgeReg[4].x = 200;
    game->ledgeReg[4].y = 0;

    game->ledgeReg[5].w = 15;
    game->ledgeReg[5].h = 75;
    game->ledgeReg[5].x = 290;
    game->ledgeReg[5].y = 132;

    game->ledgeReg[6].w = 15;
    game->ledgeReg[6].h = 70;
    game->ledgeReg[6].x = 137;
    game->ledgeReg[6].y = 140;

    game->ledgeReg[7].w = 70+15;
    game->ledgeReg[7].h = 15;
    game->ledgeReg[7].x = 210;
    game->ledgeReg[7].y = 190; 

    
    game->ledgeReg[8].w = 15;
    game->ledgeReg[8].h = 50;
    game->ledgeReg[8].x = 210;
    game->ledgeReg[8].y = 205; 

    game->ledgeReg[9].w = 142;
    game->ledgeReg[9].h = 15;
    game->ledgeReg[9].x = 87;
    game->ledgeReg[9].y = 240; 
    
    game->ledgeReg[10].w = 15;
    game->ledgeReg[10].h = 85;
    game->ledgeReg[10].x = 255;
    game->ledgeReg[10].y = 295; 

    game->ledgeReg[11].w = 15;
    game->ledgeReg[11].h = 85;
    game->ledgeReg[11].x = 380;
    game->ledgeReg[11].y = 320;

    game->ledgeReg[12].w = 100;
    game->ledgeReg[12].h = 15;
    game->ledgeReg[12].x = 330;
    game->ledgeReg[12].y = 305;

    game->ledgeReg[13].w = 15;
    game->ledgeReg[13].h = 85;
    game->ledgeReg[13].x = 330;
    game->ledgeReg[13].y = 220;

    game->ledgeReg[14].w = 15;
    game->ledgeReg[14].h = 85;
    game->ledgeReg[14].x = 415;
    game->ledgeReg[14].y = 220;

    game->ledgeReg[15].w = 100;
    game->ledgeReg[15].h = 15;
    game->ledgeReg[15].x = 380;
    game->ledgeReg[15].y = 205;

    game->ledgeReg[16].w = 15;
    game->ledgeReg[16].h = 115;
    game->ledgeReg[16].x = 463;
    game->ledgeReg[16].y = 105;

    game->ledgeReg[17].w = 115;
    game->ledgeReg[17].h = 15;
    game->ledgeReg[17].x = 420;
    game->ledgeReg[17].y = 105;

    game->ledgeReg[18].w = 15;
    game->ledgeReg[18].h = 85;
    game->ledgeReg[18].x = 380;
    game->ledgeReg[18].y = 130;

    game->ledgeReg[19].w = 15;
    game->ledgeReg[19].h = 50;
    game->ledgeReg[19].x = 420;
    game->ledgeReg[19].y = 120;

    game->ledgeReg[20].w = 40;
    game->ledgeReg[20].h = 15;
    game->ledgeReg[20].x = 340;
    game->ledgeReg[20].y = 130;

    game->ledgeReg[21].w = 15;
    game->ledgeReg[21].h = 75;
    game->ledgeReg[21].x = 340;
    game->ledgeReg[21].y = 65;

    game->ledgeReg[22].w = 55;
    game->ledgeReg[22].h = 15;
    game->ledgeReg[22].x = 285;
    game->ledgeReg[22].y = 65;

    game->ledgeReg[23].w = 15;
    game->ledgeReg[23].h = 55;
    game->ledgeReg[23].x = 370;
    game->ledgeReg[23].y = 0;

    game->ledgeReg[24].w = 70;
    game->ledgeReg[24].h = 15;
    game->ledgeReg[24].x = 535;
    game->ledgeReg[24].y = 190;

    game->ledgeReg[25].w = 15;
    game->ledgeReg[25].h = 70;
    game->ledgeReg[25].x = 535;
    game->ledgeReg[25].y = 190;

    game->ledgeReg[26].w = 110;
    game->ledgeReg[26].h = 15; 
    game->ledgeReg[26].x = 495;
    game->ledgeReg[26].y = 305;

    game->ledgeReg[27].w = 175;
    game->ledgeReg[27].h = 15; 
    game->ledgeReg[27].x = 85;
    game->ledgeReg[27].y = 320;

    game->ledgeReg[28].w = 175;
    game->ledgeReg[28].h = 15; 
    game->ledgeReg[28].x = 0;
    game->ledgeReg[28].y = -13;

    game->ledgeReg[29].w= 600;
    game->ledgeReg[29].h = 10; 
    game->ledgeReg[29].x=0; 
    game->ledgeReg[29].y=400;

    game->ledgeReg[30].w= 7;
    game->ledgeReg[30].h = 400; 
    game->ledgeReg[30].x=600; 
    game->ledgeReg[30].y=0;
}
