# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jgyles <jgyles@student.21-school.ru>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/20 22:28:49 by jgyles            #+#    #+#              #
#    Updated: 2022/02/03 19:30:32 by jgyles           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS	= 	-Wall -Wextra -Werror -g -O3

OBJDIR	=	objs
SRCDIR	=	srcs

NAME	=	minishell

LIB		=	./Libft/libft.a
SRC		=	main.c parser.c wrong_redirect.c \
			check_syntax.c line_handler.c

SRC		:=	$(addprefix $(SRCDIR)/, $(SRC))
OBJ		=	$(patsubst $(SRCDIR)/%, $(OBJDIR)/%, $(SRC:.c=.o))

all:		$(NAME)

$(NAME):	$(OBJ) $(LIB) ./includes/minishell.h
			$(CC) $(CFLAGS) $(OBJ) $(LIB) -o $(NAME)

$(OBJ):		$(OBJDIR)

$(LIB):		./Libft/libft.h
			make -C Libft/

$(OBJDIR):
			mkdir $(OBJDIR)

$(OBJDIR)/%.o:	$(SRCDIR)/%.c ./includes/minishell.h
			$(CC) $(CFLAGS) -I ./includes -c $< -o $@

clean:
			rm -rf $(OBJDIR)
			make clean -C Libft/

fclean:		clean
			rm -f $(NAME)
			make fclean -C Libft/

re:			fclean all

.PHONY:		all clean fclean re
