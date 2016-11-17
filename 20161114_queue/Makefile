# Compilers and options
CC=gcc
CPPFLAGS= -MMD
CFLAGS= -Wall -Wextra -std=c99 -g
LDFLAGS=
LDLIBS= -lm

SRC_QUEUE = testing.c queue.c
OBJ_QUEUE = ${SRC_QUEUE:.c=.o}
DEP_QUEUE = ${SRC_QUEUE:.c=.d}

SRC_TREE = tree.c queue.c
OBJ_TREE = ${SRC_TREE:.c=.o}
DEP_TREE = ${SRC_TREE:.c=.d}

all: testing tree

testing: ${OBJ_QUEUE}
tree: ${OBJ_TREE}

-include ${DEP_TREE} ${DEP_QUEUE}

clean:
	rm -f ${OBJ_QUEUE} ${DEP_QUEUE} ${OBJ_TREE} ${DEP_TREE}
	rm -f testing tree
