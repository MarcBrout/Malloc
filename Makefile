##
## Makefile for my_malloc in /home/brout_m/rendu/system/PSU_2016_malloc
## 
## Made by Brout
## Login   <marc.brout@epitech.eu>
## 
## Started on  Mon Jan 23 13:38:11 2017 Brout
## Last update Fri Jan 27 16:29:04 2017 Brout
##

MAKE_DIR=	./

NAME=		libmy_malloc.so

SRC_DIR=	./src/

SRC_FIL=	mymalloc.c \
		page.c

SRC= 		$(addprefix $(SRC_DIR), $(SRC_FIL))

OBJ=		$(SRC:.c=.o)

INC=		./include

CC=		gcc

CFLAGS=		-I$(INC) -fPIC

RM=		rm -rf

$(NAME): $(OBJ)
	$(CC) -o $(NAME) -fPIC -shared $(OBJ)

all: $(NAME)

clean:
	$(RM) $(OBJ)

fclean:
	$(RM) $(OBJ)
	$(RM) $(NAME)

re: fclean all
