output: main.o datetime.o
	g++ datetime.o main.cpp -o main -Wall       


datetime.o: datetime.cpp
	g++ -c -o datetime.o datetime.cpp -Wall


clean:
	rm *.o
	rm main
	
