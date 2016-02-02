# Author: Jayden Navarro
# Date: 1-15-2016
# Class: CMPS 112
GO           = go build -o ${EXE}
GO_SRC       = main.go
GO_EXTRA_SRC = ./huffman/encode.go ./huffman/decode.go
EXE          = huffman.exe

all : ${EXE}

${EXE} : ${GO_SRC} ${GO_EXTRA_SRC}
	${GO} ${GO_SRC}

clean :
	- rm *~

spotless : clean
	- rm -r ${EXE}
