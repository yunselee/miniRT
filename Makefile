NAME			= miniRT

CC				= gcc
CFLAGS			= -Wall -Werror -Wextra 
# -g -fsanitize=address

LIBS = ./LIBFT/libft.a
LIBV = ./Libft_vector/libvector.a

INCS_DIR		= 	-I ./LIBFT \
					-I ./mlx \
					-I ./Libft_vector \
					-I ./mlx_hook \
					-I ./print_info \
					-I ./scene \

SRCS_DIR		= 	./ \
					./SRC \
					./mlx_hook \
					./print_info \
					./scene \

SRCS			= 	main.c \
					ray.c \
					object_intersect.c \
					mlx_event.c \
					mlx_part.c \
					print_scene.c \
					print_scene2.c \
					camera.c \
					light.c \
					case_object.c \
					parsing_utils.c \
					scene1.c \
					read_file.c \
					scene2.c \


OBJS_DIR		= ./objects
OBJS			= $(addprefix $(OBJS_DIR)/, $(notdir $(SRCS:.c=.o)))
vpath %.c $(SRCS_DIR)

RM				= rm -f


all: $(NAME)

$(NAME): $(OBJS) $(LIBS) $(LIBV)
	$(CC) $(CFLAGS) -Lmlx -lmlx -framework OpenGL -framework AppKit -lm  $^ -o $@

$(OBJS_DIR)/%.o: %.c | $(OBJS_DIR)
	$(CC) $(CFLAGS) $(INCS_DIR) -c $^ -o $@

$(OBJS_DIR):
	@mkdir -p $@

# libft
$(LIBS):
	$(MAKE) -C ./LIBFT all
${LIBV} :
	@make -C ./Libft_vector all

# clean, fclean, re
clean :
	@make -C ./LIBFT clean
	@make -C ./Libft_vector clean
	$(RM) -r $(OBJS_DIR)

fclean : clean
	@make -C ./LIBFT fclean
	@make -C ./Libft_vector fclean
	${RM} ${NAME}

re: fclean all


.PHONY: all, $(NAME), clean, fclean, re