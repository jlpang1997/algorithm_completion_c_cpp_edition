main.exe:main.o fileio.o optimal_bst.o
	cc -o main.exe main.o fileio.o optimal_bst.o
	rm main.o fileio.o optimal_bst.o
main.o:fileio.h optimal_bst.h
fileio.o:fileio.h
lsc.o:optimal_bst.h

clean:
	rm main.exe