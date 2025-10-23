CC=gcc
LIB=/usr/lib
INCLUDE=/usr/include
OUT=bin/main

$(OUT): src/main.c
	$(CC) src/main.c -o $(OUT) -I$(INCLUDE)S -L$(LIB) -lmicrohttpd

run: $(OUT)
	$(OUT)
