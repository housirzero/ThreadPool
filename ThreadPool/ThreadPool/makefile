main: main.o CThread.o
	g++ main.o CThread.o -o main

main.o: main.cpp CThreadPool.h
	g++ -c main.cpp

CThread.o: CThread.cpp CThread.h CWorker.h
	g++ -c CThread.cpp

clean:
	rm -rf *.o main
