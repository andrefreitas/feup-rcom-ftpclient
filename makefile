OUT = bin/download
CC = gcc
INCLUDES = -I./include/
SRC = $(wildcard src/*.c)

all:
	$(CC) -Wall $(INCLUDES) -o $(OUT) $(SRC)