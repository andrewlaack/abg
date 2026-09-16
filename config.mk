VERSION = 10.0.0

# dirs
PREFIX = /usr/local
MANPREFIX = ${PREFIX}/share/man

# linking
LIBS = -lraylib -lX11
TLIBS = -lCatch2Main -lCatch2 ${LIBS}

# compiler
CC = g++

CFLAGS = -Ofast -std=c++23 -Wpedantic -Wall -Werror -Wextra -Wno-deprecated-declarations
CTFLAGS = -fsanitize=address,undefined -O0 -std=c++23 -Wpedantic -Wall -Werror -Wextra -Wno-deprecated-declarations

BASE_FILES = src/prim.cpp src/graph.cpp src/edge.cpp src/utils.cpp src/vertex.cpp src/background.cpp

COMMAND_P = ${CC} ${CFLAGS} 
COMMAND_S = ${BASE_FILES} ${LIBS}

TCOMMAND_P = ${CC} ${CTFLAGS} 
TCOMMAND_S = ${BASE_FILES} ${TLIBS}

# probably a good idea for debug mode to build the same as release, even though this loses out on asan and such.
# that's what tests are for.
DCOMMAND_P = ${CC} ${CFLAGS} -D NDEBUG
DCOMMAND_S = ${BASE_FILES} ${LIBS}
