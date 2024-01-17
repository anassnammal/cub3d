#include "../../inc/engine.h"
#include "../../inc/cub3d.h"

// TODO: Merge the engine headerfile and cub3d headerfile into one headerfile.

/* 
    idea : i will check with anass if i he can call this function (getting_player)
    in the parsing part cuz i need it just one time a raycasting function will be called
    multiple times so this function can make some problem cuz will change dir and pos 
    every time i call it so i will try to call it just one time in the parsing part
*/


/* 
** This function is used to get the player position and direction
** from the map. using the x and y that is given by the parsing map.
*/
void getting_player(t_scene *scene, t_player *player)
{
    /*
        at this step i need to know just 
        the player position also the direction
        of this player also i need to do something 
        here before start calculation everything 
        i will try to center the player in the middle
        of the screen

            * i need a scale factor to scale the map let's say it's 100
            * i need to know the position of the player in the map (x,y)
            * i need to know the direction of the player in the map (N,S,E,W)
        when i know all of this i can start the calculation
        so i will base on this formula to calculate the position of the player in the screen

        player.x = (x * scale) + (scale / 2)
        player.y = (y * scale) + (scale / 2)

        this formula can make the player in the middle of the screen 

        so now i need to know the direction of the player in the map
        so i will use this formula to calculate the direction of the player in the screen
        the direction will be just a char (N,S,E,W) so i will use a switch case to know the direction
        and depending on this direction i will calculate the direction of the player in the screen 

        so this is simple in math 
        if the player is looking to the north the direction will be (0,-1)
        if the player is looking to the south the direction will be (0,1)
        if the player is looking to the east the direction will be (1,0)
        if the player is looking to the west the direction will be (-1,0)
    */
    size_t x = scene->map.x_player;
    size_t y = scene->map.y_player;
    player->pos.x = (x * SCALE) + (SCALE / 2);
    player->pos.y = (y * SCALE) + (SCALE / 2);

    if (scene->map.content[x][y] == 'N')
        player->dir.y = -1 * SCALE / 4;
    if (scene->map.content[x][y] == 'W')
        player->dir.y = -1 * SCALE / 4;
    if (scene->map.content[x][y] == 'E')
        player->dir.x = SCALE / 4;
    if (scene->map.content[x][y] == 'S')
        player->dir.x = SCALE / 4;
}

t_vector p_pos(t_player player)
{
    t_vector tmp;
    t_vector dir;
    double dtmp;


    /* 
        at this step i need to know the pos of player
        on the map to start ray casting so every time 
        i will call this function from main raycasting
        function and i will get the postion of player 

        what i have :
            * i have a vector that represent to direction of player
            * also i have FOV of the player 
            * also i have the WIDTH of the screen 
        
        so
    */
}