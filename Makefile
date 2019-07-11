# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marnaud <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/07/11 17:58:28 by marnaud           #+#    #+#              #
#    Updated: 2019/07/11 17:58:30 by marnaud          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME = libft_malloc_$(HOSTTYPE).so

CC = gcc

FLAGS = -g -Wall -Wextra -Werror

INC = -I include

SRC_NAME = 	realloc.c malloc.c free.c \
			global.c show_alloc_mem.c \
			large.c small.c tiny.c \
			print_address.c


SRC_PATH = src/

SRC = $(addprefix $(SRC_PATH),$(SRC_NAME))

OBJ_NAME = $(SRC_NAME:.c=.o)

OBJ_PATH = obj/

OBJ = $(addprefix $(OBJ_PATH),$(OBJ_NAME))

all : $(NAME)

$(NAME): $(OBJ_PATH) $(OBJ)
	$(CC) $(OBJ) -o $(NAME) -shared
	@rm -rf libft_malloc.so
	ln -s $(NAME) libft_malloc.so
	@echo "\x1b[32;01m$@ SUCCESSFULLY CREATED !\x1b[32;00m"

$(OBJ_PATH):
	@mkdir -p $@

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	$(CC) $(INC) $(FLAGS) -o $@ -c $< $(INC)

clean:
	@printf "%-50s" "deleting objects..." 
	@rm -rf $(OBJ)
	@rm -rf $(OBJ_PATH)
	@printf "\033[1;32m[OK]\033[0m\n"

fclean: clean
	@printf "%-50s" "deleting executable..." 
	@rm -rf $(NAME)
	@rm -rf libft_malloc.so
	@printf "\033[1;32m[OK]\033[0m\n"

re: fclean all
