#this is a makefile use in netc
LIBS=-L/usr/lib -lm -L/$(HOME)/lib -lunp
INCLUDES=-I/usr/include -I/$(HOME)/include
DEBUG=-g
CFLAGS=-Wall -O2 $(DEBUG) $(INCLUDES)
BINDIR=./bin

hello:hello.o
	$(CC) $(CFLAGS) $(BINDIR)/$@ $? $(LIBS)

client:client.o
	$(CC) $(CFLAGS) $(BINDIR)/$@ $? (LIBS)

clean:
	rm -rf *.o


