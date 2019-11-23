main.exe:main.o fileio.o lcs.o
	cc -o main.exe main.o fileio.o lcs.o
	rm main.o fileio.o lcs.o
main.o:fileio.h lcs.h
fileio.o:fileio.h
lsc.o:lcs.h

clean:
	rm main.exe