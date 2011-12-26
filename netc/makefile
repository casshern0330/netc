HOME = /home/casshern
INCLUDE = -I$(HOME)/include
LIBS = -L$(HOME)/lib -lunp
CFLAGS = -g -O2 -Wall $(INCLUDE)

hello:hello.o
	$(CC) $(CFLAGS) -o $@ $?

client:client.o
	$(CC) $(CFLAGS) -o $@ $? $(LIBS)


#client.o:client.c
#	$(CC) $(CFLAGS) $(INCLUDE) $(LIBS) -c -o client.o client.c 

server:server.o
	$(CC) $(CFLAGS) -o $@ $? $(LIBS)

clean:
	rm -rf *.o
