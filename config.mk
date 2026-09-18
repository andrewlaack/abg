VERSION = 10.0.0

# dirs
PREFIX = /usr/local
MANPREFIX = ${PREFIX}/share/man

# linking
LIBS = -lraylib -lX11
TLIBS = -lCatch2Main -lCatch2 ${LIBS}

# compiler
CC = g++

DFLAGS = -O0 -fsanitize=address,undefined -g -std=c++23 -Wpedantic -Wall -Wextra -Wno-deprecated-declarations
CFLAGS = -Ofast -std=c++23
CTFLAGS = -fsanitize=address,undefined -O0 -std=c++23 -Wpedantic -Wall -Wextra -Wno-deprecated-declarations

BASE_FILES = src/prim.cpp src/graph.cpp src/edge.cpp src/utils.cpp src/vertex.cpp src/background.cpp

COMMAND_P = ${CC} ${CFLAGS} -D NDEBUG
COMMAND_S = ${BASE_FILES} ${LIBS}

TCOMMAND_P = ${CC} ${CTFLAGS} 
TCOMMAND_S = ${BASE_FILES} ${TLIBS}

DCOMMAND_P = ${CC} ${DFLAGS}
DCOMMAND_S = ${BASE_FILES} ${LIBS}
