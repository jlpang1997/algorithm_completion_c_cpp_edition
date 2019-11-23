objects=main.o fileio.o binary_heap.o fibo_heap.o
main.exe:$(objects)
	g++ -o main.exe $(objects)
	rm $(objects)

main.o:fileio.h binary_heap.h fibo_heap.h 
fileio.o:fileio.h 
fibo_heap.o:fibo_heap.h 
binary_heap.o:binary_heap.h 

clean:
	rm main.exe