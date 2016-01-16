# Author: Jayden Navarro
# Date: 1-15-2016
# Class: CMPS 112
GO     = go build -o ${EXE}
GO_SRC = main.go
EXE    = huffman.exe

all : ${EXE}

${EXE} : ${GO_SRC}
	${GO} ${GO_SRC}

clean :
	- rm *~

spotless : clean
	- rm -r ${EXE}
