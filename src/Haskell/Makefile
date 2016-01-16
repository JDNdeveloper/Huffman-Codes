GHC    = ghc -outputdir ${TEMP}
HS_SRC = main.hs
EXE    = huffman.exe
TEMP   = temp

all : ${EXE}

${EXE} : ${HS_SRC}
	${GHC} ${HS_SRC} -o ${EXE}

clean :
	- rm *~

spotless : clean
	- rm -r ${EXE} ${TEMP}
