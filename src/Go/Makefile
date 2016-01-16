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
