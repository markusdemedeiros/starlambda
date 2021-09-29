# Project structure:
#		./src/		a collection of .c and .h files
# 		./bin/		a .o file for all source files
#		./test/		a .test.cpp file for all source files 
#					catch.cpp, catch.hpp and catch.o
#		./			all executables dump here
#

CFLAGS = -g -Wall -Wno-unused-function
CC = gcc

DIR_BIN = ./bin
DIR_SRC = ./src
DIR_TST = ./test/catch_test

# OBJ_C :: All files in ./src/ and ./test/
# OBJ_O :: All files in ./src/*.c replaced to ./bin/*.o
# OBJ_T :: 

OBJ_C = $(wildcard ${DIR_SRC}/*.c)
OBJ_O = $(patsubst %.c,${DIR_BIN}/%.o,$(notdir ${OBJ_C}))
OBJ_T = $(patsubst %.test.cpp,exe/test-%,$(notdir $(wildcard ${DIR_TST}/*.test.cpp)))



.PHONY : clean tidy

# 	Compile rule for source .o files
all: ${OBJ_O}

#	Compile rule for entire test suite
test: ${OBJ_T} 

# 	(phony) Remove all objects compiled from ./src/
clean:
	rm $(DIR_BIN)/*.* 

# 	(phony) Remove all executables
tidy:
	rm $(OBJ_T)




#	Compile rule for test-* where * is a filename in src
exe/test-%: ${DIR_TST}/catch.o ${OBJ_O} ${DIR_SRC}/%.c 
	g++ $(CFLAGS) -o exe/test-$* ${OBJ_O} ${DIR_TST}/catch.o ${DIR_TST}/$*.test.cpp 

#	Compile rule for catch .o
${DIR_TST}/catch.o: ${DIR_TST}/catch.cpp ${DIR_TST}/catch.hpp
	g++ $(CFLAGS) -o ${DIR_TST}/catch.o -c ${DIR_TST}/catch.cpp

# 	Compile rule for objects from src
${DIR_BIN}/%.o:$(DIR_SRC)/%.c
	$(CC) $(CFLAGS) -c  $^ -o $@ 


