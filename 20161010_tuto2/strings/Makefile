# Makefile
 
CC=gcc
CPPFLAGS= -MMD -D_XOPEN_SOURCE=500
CFLAGS= -Wall -Wextra -std=c99 -O2
LDFLAGS=
LDLIBS=
 
# you should at least create empty file insert_sort.c and quick_sort.c in
# order to compile
 
SRC= mystrncpy.c
OBJ= ${SRC:.c=.o}
DEP= ${SRC:.c=.d}
 
mystrncpy: ${OBJ}
 
-include ${DEP}
 
clean:
	rm -f ${OBJ} ${DEP} main_tests
 
# END
