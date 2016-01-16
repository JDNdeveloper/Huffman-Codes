GPP   = g++ -g -O0 -Wall -Wextra -std=c++0x
C_SRC = main.cpp
H_SRC = 
O_FLS = main.o
EXE   = huffman.exe

all : ${EXE}

${EXE} : ${C_SRC} ${H_SRC} ${O_FLS}
	${GPP} ${O_FLS} -o ${EXE}

%.o : %.cpp
	${GPP} -c $<

clean :
	- rm *~ *.o

spotless : clean
	- rm ${EXE}
