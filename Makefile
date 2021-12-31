output: main.o datetime.o
	g++ *.o -o main -Wall       


datetime.o: datetime.cpp
	g++ -c -o datetime.o datetime.cpp -Wall


clean:
	rm *.o
	rm main
	
