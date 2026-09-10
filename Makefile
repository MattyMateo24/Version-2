output: test.o arbFloat.o
	g++ test.o arbFloat.o -o output

test.o: test.cpp arbFloat.h
	g++ -c test.cpp

arbFloat.o: arbFloat.cpp arbFloat.h
	g++ -c arbFloat.cpp

clean:
	rm -f *.o output