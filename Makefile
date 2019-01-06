
all:
	g++ -Wall -Wextra -O3 -march=native *.cpp -o main

debug:
	g++ -Wall -Wextra -g -march=native *.cpp -o main.debug

clean:
	rm -f main main.debug *.o *~
