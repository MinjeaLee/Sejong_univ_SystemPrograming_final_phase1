# Makefile
# * Author : Lee Minjae
# * ID     : 21011741
# * dept   : Information Security
# * date   : 2023.12.06
# * Contact: leejoy2@sju.ac.kr
# * repo   : https://github.com/MinjeaLee/Sejong_univ_SystemPrograming_final_phase1
#

NAME_S = server
NAME_C_A = client_add
NAME_C_M = client_mul

CC = cc

SRC_C_A = ./client_add.c
SRC_C_M = ./client_mul.c
SRC_S = ./server.c

INC_C = ./client.h
INC_S = ./server.h

OBJ_C_A = $(SRC_C_A:.c=.o)
OBJ_C_M = $(SRC_C_M:.c=.o)
OBJ_S = $(SRC_S:.c=.o)


all: $(NAME_S) $(NAME_C_A) $(NAME_C_M)

.c.o: 
	$(CC) -c $< -o $@ 

$(NAME_S): $(OBJ_S) 
	$(CC) $^ -o $@ -I$(INC_S)

$(NAME_C_A): $(OBJ_C_A)
	$(CC) $^ -o $@ -I$(INC_C)

$(NAME_C_M): $(OBJ_C_M)
	$(CC) $^ -o $@ -I$(INC_C)

re: fclean all

clean:
	rm -f $(OBJ_C_A) $(OBJ_C_M) $(OBJ_S)

fclean: clean
	rm -f $(NAME_S) $(NAME_C_A)	$(NAME_C_M)

.PHONY: all clean fclean re