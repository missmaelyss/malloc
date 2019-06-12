ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME = libft_malloc_$(HOSTTYPE).so

CC = gcc

FLAGS = -g -Wall -Wextra

INC = -I include

SRC_NAME = global.c malloc.c free.c realloc.c show_alloc_mem.c

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
