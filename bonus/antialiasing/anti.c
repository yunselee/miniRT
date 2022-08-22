#include "resolution.h"
#include "anti.h"
#include "mlx_manager.h"
#include "color.h"
#include "assert.h"

static unsigned int *get_board()
{
	static unsigned int board[WIN_HEIGHT][WIN_WIDTH];

	return (unsigned int*)board;
}

static unsigned int ft_mlx_get_pixel_color(t_image *img, int x, int y)
{
	char	*dst;

	dst = img->addr + (y * img->line + x * (img->bpp / 8));
	return *(unsigned int*)dst;
}

void antialiasing()
{
	t_mlx_manager *mlx;
	unsigned int *board;
	int i;
	int j;
	unsigned int t;
	
	int dirXY[3] =
	{
		-1, 0, 1
	};
	board = get_board();
	mlx = get_mlx();
	
	j = 0;
	while(j < WIN_HEIGHT)
	{
		i = 0;
		while(i < WIN_WIDTH)
		{
			int n = 0;
			
			int rgb[3] = {0,0,0};			
			int a = 0;
			while(a < 3)
			{
				int b = 0;
				while(b < 3)
				{
					int x = i + dirXY[a];
					int y = j + dirXY[b];
					if(
						x >= 0 && x < WIN_WIDTH &&
						y >= 0 && y < WIN_HEIGHT
					)
					{
						t = ft_mlx_get_pixel_color(&mlx->image, x, y);
						rgb[0] += (t >> 16) &0xFF;
						rgb[1] += (t >> 8) &0xFF;
						rgb[2] += (t) &0xFF;;

						n++;
					}
					b++;
				}
				a++;
			}
			assert(n != 0);
			rgb[0] /= n;
			rgb[1] /= n;
			rgb[2] /= n;
			*(board + WIN_WIDTH * j + i) = (rgb[0] << 16) + (rgb[1] << 8 )+ rgb[2];
			//(unsigned int)c.blue + (c.green << 8) + (c.red << 16));
			i++;
		}
		j++;
	}

	j = 0;
	while (j < WIN_HEIGHT)
	{
		i = 0;
		while(i < WIN_WIDTH)
		{
			ft_mlx_set_pixel_color(&mlx->image, i, \
							j, *(board + WIN_WIDTH * j + i));
			i++;
		}
		j++;
	}
}



// 	void	ft_mlx_set_pixel_color(t_image *img, unsigned int x, \
// 							unsigned int y, unsigned int color)
// {
// 	char	*dst;

// 	dst = img->addr + (y * img->line + x * (img->bpp / 8));
// 	*(unsigned int *)dst = color;
// }