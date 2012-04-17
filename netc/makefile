#HOME = /home/casshern
UNPHOME = /cygdrive/d/library/unpv13e
INCLUDE = -I$(UNPHOME)/include
LIBS = -L$(UNPHOME) -lunp
CFLAGS = -g -O2 -Wall $(INCLUDE)
BINDIR=./bin

CC = gcc

all:hello client server

hello:hello.o
	$(CC) $(CFLAGS) -o $(BINDIR)/$@ $?

client:client.o
	$(CC) $(CFLAGS) -o $(BINDIR)/$@ $? $(LIBS)

server:server.o
	$(CC) $(CFLAGS) -o $(BINDIR)/$@ $? $(LIBS)

udpclient:udpclient.o
	$(CC) $(CFLAGS) -o $(BINDIR)/$@ $? $(LIBS)

udpserver:udpserver.o
	$(CC) $(CFLAGS) -o $(BINDIR)/$@ $? $(LIBS)

mygetaddrinfo:mygetaddrinfo.o
	rm -rf $(BINDIR)/$@
	$(CC) $(CFLAGS) -o $(BINDIR)/$@ $? $(LIBS)

clean:
	rm -rf *.o
