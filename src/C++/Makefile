# Author: Jayden Navarro
# Date: 1-15-2016
# Class: CMPS 112
GPP   = g++ -g -O0 -Wall -Wextra -std=c++11
C_SRC = main.cpp huffman.cpp
H_SRC = huffman.h
O_FLS = main.o huffman.o
EXE   = huffman.exe

all : ${EXE}

${EXE} : ${C_SRC} ${H_SRC} ${O_FLS}
	${GPP} ${O_FLS} -o ${EXE}

%.o : %.cpp
	${GPP} -c $<

clean :
	- rm *~ *.o *.enc *.dec

spotless : clean
	- rm ${EXE}
