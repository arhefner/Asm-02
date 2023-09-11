GETOPT := getopt

PROJECT = asm02
CC = gcc
DEFS = -Wall
INCS =
INCDIR =
LIBS =
LIBDIR =
OBJS = \
	asm.o mmap.o

ifeq ($(GETOPT),ya_getopt)
  DEFS += -DUSE_YA_GETOPT
  OBJS += ya_getopt.o
else ifneq ($(GETOPT),getopt)
  $(error GETOPT must be getopt or ya_getopt)
endif

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
