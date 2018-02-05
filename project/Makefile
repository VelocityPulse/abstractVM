# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cchameyr <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/02/05 10:57:06 by cchameyr          #+#    #+#              #
#    Updated: 2018/02/05 11:07:35 by cchameyr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

OBJECTS_NAME_FOLDER = objects

SOURCES_NAME_FOLDER = sources

FILES =				main.cpp \

SRCS =				$(addprefix $(SOURCES_NAME_FOLDER)/, $(FILES))

OBJS =				$(addprefix $(OBJECTS_NAME_FOLDER)/, $(FILES:.cpp=.o))

CC =				clang++

NAME =				avm

DEBUGSEGFAULT =		-g3 -fsanitize=address

FLAGS =				-Wall -Wextra -Werror #$(DEBUGSEGFAULT)

RM =				rm -rf

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o $(NAME)

$(OBJS):
	$(CC) $(FLAGS) -c $(SRCS)
	@make objs_mv

objs_mv:
	@mkdir $(OBJECTS_NAME_FOLDER)
	@mv $(FILES:.cpp=.o) $(OBJECTS_NAME_FOLDER)

objs_rm:
	@$(RM) $(OBJECTS_NAME_FOLDER)
	@$(RM) $(FILES:.cpp=.o)

clean: objs_rm

fclean: clean
	$(RM) $(NAME)

re: fclean all

r: objs_rm
	$(RM) $(NAME)
	@make
