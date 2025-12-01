CC=gcc
LIB=/usr/lib
INCLUDE=/usr/include
OUT=bin/main

$(OUT): src/main.c
	$(CC) src/main.c -o $(OUT) -I$(INCLUDE) -Iinclude -L$(LIB) -lmicrohttpd

run: $(OUT)
	$(OUT)
