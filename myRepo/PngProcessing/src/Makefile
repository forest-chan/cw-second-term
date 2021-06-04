all: main.o imageProcessing.o writePngFile.o readPngFile.o printHelp.o
	gcc main.o imageProcessing.o writePngFile.o readPngFile.o printHelp.o -lpng -o cw2

main.o: main.c structs.h defines.h imageProcessing.h
		gcc -c -lpng main.c

imageProcessing.o: imageProcessing.c structs.h defines.h imageProcessing.h
		gcc -c -lpng imageProcessing.c

writePngFile.o: writePngFile.c structs.h defines.h imageProcessing.h
		gcc -c -lpng writePngFile.c

readPngFile.o: readPngFile.c structs.h defines.h imageProcessing.h
		gcc -c -lpng readPngFile.c

printHelp.o: printHelp.c imageProcessing.h
		gcc -c -lpng printHelp.c

clean:
		rm -rf *.o