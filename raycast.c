#include "lib/MLX42/include/MLX42/MLX42.h"
#include <stdio.h>
#include <string.h>
#include <math.h>

#define MAP_WIDTH 10
#define MAP_HEIGHT 10
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

typedef struct s_vector2d{
    double x;
    double y;
} t_vector2d;

t_vector2d  vec_new(double x, double y)
{
    t_vector2d  v;

    v.x = x;
    v.y = y;
    return (v);
}

t_vector2d  vec_add(t_vector2d a, t_vector2d b)
{
    return (vec_new(a.x + b.x, a.y + b.y));
}

t_vector2d  vec_sub(t_vector2d a, t_vector2d b)
{
    return (vec_new(a.x - b.x, a.y - b.y));
}

t_vector2d  vec_mul(t_vector2d a, double b)
{
    return (vec_new(a.x * b, a.y * b));
}

t_vector2d  vec_div(t_vector2d a, double b)
{
    return (vec_new(a.x / b, a.y / b));
}

double  vec_dot(t_vector2d a, t_vector2d b)
{
    return (a.x * b.x + a.y * b.y);
}

double  vec_cross(t_vector2d a, t_vector2d b)
{
    return (a.x * b.y - a.y * b.x);
}

double  vec_len(t_vector2d a)
{
    return (sqrt(vec_dot(a, a)));
}

t_vector2d  vec_norm(t_vector2d a)
{
    return (vec_div(a, vec_len(a)));
}

t_vector2d  vec_rot(t_vector2d a, double angle)
{
    return (vec_new(a.x * cos(angle) - a.y * sin(angle), a.x * sin(angle) + a.y * cos(angle)));
}

// Map data (0 = no wall, 1 = wall)
int map[MAP_HEIGHT][MAP_WIDTH] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 1, 1, 1, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 1, 0, 1},
    {1, 0, 0, 0, 1, 1, 0, 1, 0, 1},
    {1, 0, 0, 0, 1, 1, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

mlx_t *mlx;
mlx_image_t *frame;

// Player position and direction
t_vector2d player = {2.5, 2.5};
t_vector2d playerDir = {1, 0};
t_vector2d playerPlane = {0, 0.66};

void castRays() {
    // variables for ray position and direction
    double camera_x;
    t_vector2d rayDir;
    // variables for DDA
    t_vector2d rayPos;
    double stepSize;
    // variables for distance to wall
    double distance;
    // variables for wall height
    int wallHeight;
    int wallStart;
    int wallEnd;

    

    for (int x = 0; x < SCREEN_WIDTH; ++x) {
        // Calculate ray direction and camera plane
        camera_x = 2 * x / (double)SCREEN_WIDTH - 1;
        rayDir = vec_add(playerDir, vec_mul(playerPlane, camera_x));

        // DDA algorithm
        rayPos = player;
        if (rayDir.y == 0) {
            rayDir.y = 1e30;
        }
        if (rayDir.x == 0) {
            rayDir.x = 1e30;
        }
        stepSize = vec_len(vec_new(1 / rayDir.x, 1 / rayDir.y));
        rayDir = vec_mul(rayDir, stepSize); // Cast stepSize to unsigned int
        // ... (perform DDA steps)
        while (map[(int)round(rayPos.x)][(int)round(rayPos.y)] == 0) {
            printf("rayPos.x: %f, rayPos.y: %f\n", rayPos.x, rayPos.y);
            rayPos = vec_add(rayPos, vec_mul(rayDir, stepSize));
        }

        // Calculate distance to wall
        distance = vec_len(vec_sub(rayPos, player));

        // Draw wall column based on distance
        wallHeight = (int)(SCREEN_HEIGHT / distance);
        if (wallHeight == -2147483648)
            wallHeight = SCREEN_HEIGHT;
        wallStart = -wallHeight / 2 + SCREEN_HEIGHT / 2;
        if (wallStart < 0) {
            wallStart = 0;
        }
        wallEnd = wallHeight / 2 + SCREEN_HEIGHT / 2;
        if (wallEnd >= SCREEN_HEIGHT) {
            wallEnd = SCREEN_HEIGHT - 1;
        }
        for (int y = wallStart; y < wallEnd; ++y) {
            mlx_put_pixel(frame, x, y, 0x00FF00FF);
        }

        // Repeat for other columns
    }
}

void key_hook(void *param) {
    (void)param;
    if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE)) {
        mlx_terminate(mlx);
    }
    if (mlx_is_key_down(mlx, MLX_KEY_W)) {
        // Move forward
        player = vec_add(player, playerDir);
    }
    if (mlx_is_key_down(mlx, MLX_KEY_S)) {
        // Move backward
        player = vec_sub(player, playerDir);
    }
    if (mlx_is_key_down(mlx, MLX_KEY_A)) {
        // Move left
        player = vec_sub(player, playerPlane);
    }
    if (mlx_is_key_down(mlx, MLX_KEY_D)) {
        // Move right
        player = vec_add(player, playerPlane);
    }
    if (mlx_is_key_down(mlx, MLX_KEY_LEFT)) {
        // Rotate left
        playerDir = vec_rot(playerDir, -0.1);
        playerPlane = vec_rot(playerPlane, -0.1);
    }
    if (mlx_is_key_down(mlx, MLX_KEY_RIGHT)) {
        // Rotate right
        playerDir = vec_rot(playerDir, 0.1);
        playerPlane = vec_rot(playerPlane, 0.1);
    }
    memset(frame->pixels, 0, SCREEN_WIDTH * SCREEN_HEIGHT * 4);
    castRays();
}

int main() {
    mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "Raycasting", false);
    if (!mlx) {
        printf("Error: Could not initialize MLX\n");
        return 1;
    }
    frame = mlx_new_image(mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
    if (!frame) {
        printf("Error: Could not create frame\n");
        return 1;
    }
    castRays();
    if (mlx_image_to_window(mlx, frame, 0, 0) < 0) {
        printf("Error: Could not display frame\n");
        return 1;
    }
    mlx_loop_hook(mlx, key_hook, NULL);
    mlx_loop(mlx);
    mlx_delete_image(mlx, frame);
    mlx_terminate(mlx);
    return 0;
}