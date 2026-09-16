VERSION = 10.0.0

# dirs
PREFIX = /usr/local
MANPREFIX = ${PREFIX}/share/man

# linking
LIBS = -lraylib -lX11
TLIBS = -lCatch2Main -lCatch2 ${LIBS}

# compiler
CC = g++

CFLAGS = -Ofast -std=c++23 -Wpedantic -Wall -Werror -Wextra -Wno-deprecated-declarations -Os 
CTFLAGS = -fsanitize=address,undefined -O0 -std=c++23 -Wpedantic -Wall -Werror -Wextra -Wno-deprecated-declarations -Os

BASE_FILES = src/prim.cpp src/graph.cpp src/edge.cpp src/utils.cpp src/vertex.cpp src/background.cpp

COMMAND_P = ${CC} ${CFLAGS} 
COMMAND_S = ${BASE_FILES} ${LIBS}

TCOMMAND_P = ${CC} ${CTFLAGS} 
TCOMMAND_S = ${BASE_FILES} ${TLIBS}
