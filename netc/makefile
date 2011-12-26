HOME = /home/casshern
INCLUDE = -I$(HOME)/include
LIBS = -L$(HOME)/lib -lunp
CFLAGS = -g -O2 -Wall $(INCLUDE)
BINDIR=./bin

all:hello client server

hello:hello.o
	$(CC) $(CFLAGS) -o $(BINDIR)/$@ $?

client:client.o
	$(CC) $(CFLAGS) -o $(BINDIR)/$@ $? $(LIBS)

server:server.o
	$(CC) $(CFLAGS) -o $(BINDIR)/$@ $? $(LIBS)

clean:
	rm -rf *.o
