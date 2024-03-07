NAME		:= cub3d
INCDIR		:= inc
SRCDIR		:= src
OBJDIR		:= obj
LIBDIR		:= lib
LIBMLX		:= $(LIBDIR)/MLX42
LIBFT		:= $(LIBDIR)/libft
HEADERS		:= $(wildcard $(INCDIR)/*.h)
SOURCES		:= $(wildcard $(SRCDIR)/*.c)
OBJECTS		:= $(addprefix $(OBJDIR)/, $(notdir $(patsubst %.c, %.o, $(SOURCES))))
CCOMPILER	:= cc
CFLAGS		:= -g -Werror -Wall -Wextra -fsanitize=address,undefined
INCFLAG		:= -I$(INCDIR) -I$(LIBFT) -I$(LIBMLX)/include

ifeq ($(shell uname), Darwin)
	CLIBRARY:=-L$(LIBFT) -L$(LIBMLX)/build -lft -lmlx42 -lglfw
else
	CLIBRARY:=-L$(LIBDIR) -lft -lmlx42 -ldl -lglfw -pthread -lm
endif

all: $(NAME)

$(NAME): libft libmlx $(OBJDIR) $(OBJECTS)
	$(CCOMPILER) $(CFLAGS) $(OBJECTS) $(CLIBRARY) -o $@

libft:
	make -C $(LIBFT)
	make bonus -C $(LIBFT)
	make gnl -C $(LIBFT)

libmlx:
	brew list glfw 2>&1 > /dev/null || brew install glfw
	cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(HEADERS)
	$(CCOMPILER) $(CFLAGS) -c $< $(INCFLAG) -o $@

$(OBJDIR):
	mkdir -p $@

clean:
	make clean -C $(LIBFT)
	rm -rf $(OBJDIR)

fclean: clean
	make fclean -C $(LIBFT)
	rm -rf $(LIBMLX)/build
	rm -rf $(NAME)

re: fclean all

.PHONY : all libft libmlx clean fclean re
