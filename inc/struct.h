/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelmrabe <aelmrabe@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 18:59:18 by aelmrabe          #+#    #+#             */
/*   Updated: 2024/01/02 16:27:29 by aelmrabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

/**
**	Structures for the player
* @param direction: will be (N)orth, (S)outh, (E)ast, (W)est
* @param position_x, position_y the x and y position of the player
* @param direction_x, direction_y the x and y direction of the player
* @param plane_x, plane_y the x and y in 2d space of the camera
* @param moves_x, moves_y the x and y of the player's moves (W,A,S,D)(-1,-1,1,1)
* @param rotation the rotation of the player (left, right)(-1,1);
*/

typedef struct s_player{
    char direction;
    double position_x;
    double position_y;
    double direction_x;
    double direction_y;
    double plane_x;
    double plane_y;
    int moves_x;
    int moves_y;
    int rotation;
}t_player;

/**
 * Structures for the view
 * 
*/
typedef struct s_ray{
    double multi;
    double dir_x;
    double dir_y;
    int map_x;
    int map_y;
    int step_x;
    int step_y;
    double side_x;
    double side_y;
    double delta_x;
    double delta_y;
    double wall_x;
    bool hit;
    int line_height;
    int draw_start;
}t_ray;

typedef struct s_screen{
    int width;
    int height;
    int endian;
    int size_line;
    int pixel_bits;
    void *img;
    void *addr;
}t_screen;


/**
 * Structures for the view
    * @param x, y the x and y of the screen
    * @param i, j the i and j of the map
    * @param color the color of the pixel
    * @param mlx the mlx pointer
    * @param win the window pointer
    * @param screen the screen pointer
*/
typedef struct s_view{
    int x;
    int y;
    int i;
    int j;
    int color;
}t_view;


#endif