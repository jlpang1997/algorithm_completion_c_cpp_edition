objects=main.o fileio.o pattern_regulation.o
main.exe:$(objects)
	g++ -o main.exe $(objects)
	rm $(objects)

main.o:fileio.h pattern_regulation.h
pattern_regulation.o:pattern_regulation.h
clean:
	rm main.exe























