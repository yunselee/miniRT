NAME			= miniRT

CC				= gcc
CFLAGS			=  -Wall -Werror -Wextra -O2
# -g -fsanitize=address  -Wall -Werror -Wextra

LIBS = ./library/LIBFT/libft.a
LIBV = ./library/Libft_vector/libvector.a
MLX = -Llibrary/mlx -lmlx -framework OpenGL -framework AppKit

INCS_DIR		= 	-I ./library/LIBFT \
					-I ./library/mlx \
					-I ./library/Libft_vector \
					-I ./mlx_manager \
					-I ./print_info \
					-I ./scene \
					-I ./color \
					-I ./ray_cast \
					-I ./timer \
					-I ./quadrics \
					-I ./scene_editer \
					-I .

SRCS_DIR		= 	./ \
					./ray_cast \
					./color \
					./print_info \
					./mlx_manager \
					./scene \
					./timer \
					./quadrics \
					./scene_editer \



SRCS			= 	main.c \
					\
					ray.c \
					light_source.c \
					reflection.c \
					diffuse_reflection.c \
					specular_reflection.c \
					ray_thread.c \
					\
					color.c \
					color_disruption.c \
					get_texture_color.c \
					\
					print_scene.c \
					print_scene2.c \
					\
					mlx_event.c \
					mlx_mouse.c \
					mlx_mouse_wheel.c \
					mlx_keyboard_move.c \
					mlx_keyboard.c \
					mlx_manager.c \
					\
					camera.c \
					light.c \
					parsing_utils.c \
					read_file.c \
					scene1.c \
					scene2.c \
					\
					timer.c \
					\
					quadrics.c \
					quadrics_helper.c \
					quadrics_equations.c \
					\
					scene_editer.c \


OBJS_DIR		= ./OBJS
OBJS			= $(addprefix $(OBJS_DIR)/, $(notdir $(SRCS:.c=.o)))
vpath %.c $(SRCS_DIR)

RM				= rm -f

all: $(NAME)

$(NAME): $(OBJS) $(LIBS) $(LIBV)
	$(CC) $(CFLAGS) $(MLX) -lm  $^ -o $@

$(OBJS_DIR)/%.o: %.c | $(OBJS_DIR)
	$(CC) $(CFLAGS) $(INCS_DIR) -c $^ -o $@

$(OBJS_DIR):
	@mkdir -p $@

# libft
$(LIBS):
	$(MAKE) -C ./library/LIBFT all
${LIBV} :
	@make -C ./library/Libft_vector all

# clean, fclean, re
clean :
	@make -C ./library/LIBFT clean
	@make -C ./library/Libft_vector clean
	$(RM) -r $(OBJS_DIR)

fclean : clean
	@make -C ./library/LIBFT fclean
	@make -C ./library/Libft_vector fclean
	${RM} ${NAME}

re: fclean all

.PHONY: all, $(NAME), clean, fclean, re