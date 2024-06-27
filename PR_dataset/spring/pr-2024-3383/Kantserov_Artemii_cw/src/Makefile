all: cw_work

cw_work: main.cpp command.cpp draw.cpp mirror.cpp portable_network_graphic.cpp
	g++ -std=c++14 main.cpp command.cpp draw.cpp mirror.cpp portable_network_graphic.cpp -lpng -o cw

clean:
	rm -rf *.o cw_work