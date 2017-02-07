##
## Makefile for my_malloc in /home/brout_m/rendu/system/PSU_2016_malloc
##
## Made by Brout
## Login   <marc.brout@epitech.eu>
##
## Started on  Mon Jan 23 13:38:11 2017 Brout
## Last update Tue Feb  7 12:01:30 2017 brout_m
##

MAKE_DIR=	./

NAME=		libmy_malloc.so

SRC_DIR=	./src/

SRC_FIL=	mymalloc.c \
		page.c \
		myfree.c \
		myrealloc.c \
		mycalloc.c \
		show_alloc_mem.c

SRC= 		$(addprefix $(SRC_DIR), $(SRC_FIL))

OBJ=		$(SRC:.c=.o)

INC=		./include

CC=		gcc

CFLAGS=		-I$(INC) -fPIC -W -Wall -Wextra -Werror

LDFLAGS=

RM=		rm -rf

$(NAME): $(OBJ)
	$(CC) -o $(NAME) -fPIC -shared $(OBJ) $(LDFLAGS)

all: $(NAME)

clean:
	$(RM) $(OBJ)

fclean:
	$(RM) $(OBJ)
	$(RM) $(NAME)

re: fclean all
