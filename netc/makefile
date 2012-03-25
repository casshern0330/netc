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

udpclient:udpclient.o
	$(CC) $(CFLAGS) -o $(BINDIR)/$@ $? $(LIBS)

udpserver:udpserver.o
	$(CC) $(CFLAGS) -o $(BINDIR)/$@ $? $(LIBS)

mygetaddrinfo:mygetaddrinfo.o
	rm -rf $(BINDIR)/$@
	$(CC) $(CFLAGS) -o $(BINDIR)/$@ $? $(LIBS)

clean:
	rm -rf *.o
