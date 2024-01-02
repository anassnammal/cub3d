NAME=cub3d
INCDIR=inc
SRCDIR=src
OBJDIR=obj
LIBDIR=libft
HEADER=$(INCDIR)/$(NAME:=.h)
SOURCES=$(wildcard $(SRCDIR)/*.c)
OBJECTS=$(addprefix $(OBJDIR)/, $(notdir $(patsubst %.c, %.o, $(SOURCES))))
LIBFT=libft.a

CCOMPILER=cc
CLIBRARY=-L$(LIBDIR) -lft -lmlx -lXext -lX11 -lm -lz
CFLAGS=-g -Werror -Wall -Wextra


all: $(NAME)

$(NAME): $(LIBFT) $(OBJDIR) $(OBJECTS)
	$(CCOMPILER) $(CFLAGS) $(OBJECTS) $(CLIBRARY) -o $@

$(LIBFT):
	make -C $(LIBDIR)
	make bonus -C $(LIBDIR)
	make gnl -C $(LIBDIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(HEADER)
	$(CCOMPILER) $(CFLAGS) -c $< -I $(INCDIR) -o $@

$(OBJDIR):
	mkdir -p $@

clean:
	make clean -C $(LIBDIR)
	rm -rf $(OBJDIR)

fclean: clean
	make fclean -C $(LIBDIR)
	rm -rf $(NAME)

re: fclean all

.PHONY : all clean fclean re
