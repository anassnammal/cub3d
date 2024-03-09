#include "lib/MLX42/include/MLX42/MLX42.h"

int main()
{
	mlx_t	*mlx = mlx_init(, "ff", false);
	mlx_image_t	*i = mlx_new_image(mlx, 2,2);
	mlx_image_to_window(mlx, i, 0, 0);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return 0;
}
