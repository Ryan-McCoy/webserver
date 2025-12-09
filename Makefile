CC=gcc
LIB=/usr/lib
INCLUDE=/usr/include
OUT=bin/main
DEBUG=bin/debug
OUTPUTDIR=bin

$(OUT): src/main.c $(OUTPUTDIR)
	$(CC) src/main.c -o $(OUT) -I$(INCLUDE) -Iinclude -L$(LIB) -lmicrohttpd

$(DEBUG): src/main.c $(OUTPUTDIR)
	$(CC) src/main.c -o $(DEBUG) -I$(INCLUDE) -Iinclude -L$(LIB) -lmicrohttpd  -DDEBUG

run: $(DEBUG)
	$(DEBUG)

debug: $(DEBUG)

$(OUTPUTDIR): 
	mkdir $(OUTPUTDIR)