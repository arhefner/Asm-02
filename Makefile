PROJECT = asm02
CC = gcc
DEFS = -Wall
INCS =
INCDIR =
LIBS =
LIBDIR =
OBJS = \
	asm.o

$(PROJECT): $(OBJS)
	$(CC) $(DEFS) $(LIBDIR) $(OBJS) $(LIBS) -o $(PROJECT)

.c.o:
	$(CC) $(DEFS) $(INCDIR) $(INCS) -c $<

clean:
	-rm *.o
	-rm $(PROJECT)

install:
	cp asm02 /usr/local/bin/
	chmod a+rx /usr/local/bin/asm02

asm.o:           header.h asm.c
