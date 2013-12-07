
# -= powerpc (DS108j) =- #
#CC=../powerpc-linux/bin/powerpc-linux-gcc
#LD=../powerpc-linux/bin/powerpc-linux-ld
#CFLAGS += -I../powerpc-linux/include
#LDFLAGS+= -L../powerpc-linux/lib
#OUTDIR=powerpc

# -= local =- #
#CC=gcc
CC=g++
LD=ld
OUTDIR=bin/
SRC=src/

all: init

clean:
	rm -rf *.o

#
# programmes
#

init: init.o np.o
	$(CC) -o $(OUTDIR)/samples/init init.o np.o

#
# sources
#

mem_socket.o: $(SRC)mem_socket.c
	$(CC) -o mem_socket.o -c $(SRC)mem_socket.c -W -Wall -ansi -pedantic

np.o: sys1.c
	$(CC) -o sys1.o -c $(SRC)sys1.c $(SRC)lib/stack.c $(SRC)lib/id.c $(SRC)lib/desc.c -W -Wall -ansi -pedantic
	
#
# samples
#

init.o: samples/init.c
	$(CC) -o init.o -c samples/init.c -W -Wall -ansi -pedantic
	